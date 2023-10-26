#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "myopenglwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  // сохранение
  QSettings settings("MyCompany", "MyApp");
  ui->openglwidget->setBackgroundColor(
      settings.value("backgroundColor").value<QColor>());
  LineStyle style = (LineStyle)settings.value("lineStyle").toInt();
  ui->openglwidget->setLineStyle(style);
  VertexStyle style2 = (VertexStyle)settings.value("vertexStyle").toInt();
  ui->openglwidget->setVertexStyle(style2);
  float thickness = settings.value("thickness").toFloat();
  ui->openglwidget->setThickness(thickness);
  QColor edgeColor = settings.value("edgeColor").value<QColor>();
  ui->openglwidget->setEdgeColor(edgeColor);
  QColor vertexColor = settings.value("vertexColor").value<QColor>();
  ui->openglwidget->setVertexColor(vertexColor);
  float thickness_of_vertexes =
      settings.value("thickness_of_vertexes").toFloat();
  ui->openglwidget->setThicknessVertexes(thickness_of_vertexes);
  ProjectionType type = (ProjectionType)settings.value("projection").toInt();
  ui->openglwidget->setProjectionType(type);
  // выбор цвет ребра
  connect(ui->edgeColor, &QPushButton::clicked, [=]() {
    QColor color = QColorDialog::getColor(ui->openglwidget->edgeColor);
    if (color.isValid()) {
      ui->openglwidget->setEdgeColor(color);
    }
  });
  //выбор цветы вершины
  connect(ui->vertexColor, &QPushButton::clicked, [=]() {
    QColor color = QColorDialog::getColor(ui->openglwidget->vertexColor);
    if (color.isValid()) {
      ui->openglwidget->setVertexColor(color);
    }
  });
  // выбор пунктир или сплошная
  connect(ui->edge_dash, &QRadioButton::toggled, [=](bool checked) {
    if (checked) {
      ui->openglwidget->setLineStyle(DASHED);
    }
  });
  connect(ui->edge_solid, &QRadioButton::toggled, [=](bool checked) {
    if (checked) {
      ui->openglwidget->setLineStyle(SOLID);
    }
  });
  //выбор проекции
  connect(ui->central_button, &QRadioButton::toggled, [=](bool checked) {
    if (checked) {
      ui->openglwidget->setProjectionType(CENTRAL);
    }
  });
  connect(ui->parallel_button, &QRadioButton::toggled, [=](bool checked) {
    if (checked) {
      ui->openglwidget->setProjectionType(PARALLEL);
    }
  });
  //выбор вершины
  connect(ui->none_button, &QRadioButton::toggled, [=](bool checked) {
    if (checked) {
      ui->openglwidget->setVertexStyle(NONE);
    }
  });
  connect(ui->circle_button, &QRadioButton::toggled, [=](bool checked) {
    if (checked) {
      ui->openglwidget->setVertexStyle(CIRCLE);
    }
  });
  connect(ui->square_button, &QRadioButton::toggled, [=](bool checked) {
    if (checked) {
      ui->openglwidget->setVertexStyle(SQUARE);
    }
  });
  // толщина ребра
  connect(ui->edge_thickness, &QSlider::valueChanged, [=](int value) {
    float thick = value / 20.0f;  // Map to range
    ui->openglwidget->setThickness(thick);
  });
  // толщина вершины
  connect(ui->vertex_thickness, &QSlider::valueChanged, [=](int value) {
    float thick = value;  // Map to range
    ui->openglwidget->setThicknessVertexes(thick);
  });
  // кнопка open
  connect(ui->openButton, SIGNAL(clicked()), this, SLOT(openButtonClicked()));
  //гифки
  timer = new QTimer(0);
  connect(timer, SIGNAL(timeout()), this, SLOT(make_gif()));
  ui->centralwidget->setStyleSheet(styleSheet);
}

MainWindow::~MainWindow() {
  if (ui->openglwidget->is_data_parsed && !ui->openglwidget->in) {
    fclose(ui->openglwidget->in);
    clear_memory(ui->openglwidget->info);
    clear_memory(ui->openglwidget->buff_info);
  }
  saveSettings();
  delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Escape)
    close();
  else
    QWidget::keyPressEvent(e);
}

void MainWindow::openButtonClicked() {
  mainwindow_filename = QFileDialog::getOpenFileName(
      this, tr("Open .obj file:"), "~/", tr("Obj Files (*.obj)"));
  if (!mainwindow_filename.isEmpty() && !mainwindow_filename.isNull()) {
    QStringList pieces = mainwindow_filename.split("/");
    fileNameWithoutPath =
        pieces.value(pieces.length() - 1);  // to get file name without path
    ui->fileNameLabel->setText(fileNameWithoutPath);
    ui->filePathLabel->setText(mainwindow_filename);
    ui->openglwidget->opengl_filename = mainwindow_filename;
    ui->openglwidget->parse_obj();
    if (ui->openglwidget->is_data_parsed) {
      ui->xRotSlider->setValue(0);
      ui->yRotSlider->setValue(0);
      ui->zRotSlider->setValue(0);
      ui->xTransSlider->setValue(0);
      ui->yTransSlider->setValue(0);
      ui->zTransSlider->setValue(0);
      ui->scaleSlider->setValue(0);
    }
    ui->verticesCountLabel->setText(
        QString::number(ui->openglwidget->info->count_of_vertexes));
    ui->edgesCountLabel->setText(
        QString::number(ui->openglwidget->info->count_of_facets));
  } else {
    msg.showMessage("Please open the file to view the image!\n");
  }
}

void MainWindow::on_xRotSlider_valueChanged(int value) {
  ui->yRotSlider->setValue(0);
  ui->zRotSlider->setValue(0);
  if (ui->openglwidget->is_data_parsed) {
    copy_data(ui->openglwidget->info, ui->openglwidget->buff_info);
    rotation_by_ox(ui->openglwidget->info, value / M_PI / 30);
    if (ui->openglwidget->save_move_x != 0) {
      move_x(ui->openglwidget->info, ui->openglwidget->save_move_x);
    }
    if (ui->openglwidget->save_move_y != 0) {
      move_y(ui->openglwidget->info, ui->openglwidget->save_move_y);
    }
    if (ui->openglwidget->save_move_z != 0) {
      move_z(ui->openglwidget->info, ui->openglwidget->save_move_z);
    }
    if (ui->openglwidget->save_scale != 0) {
      scaling(ui->openglwidget->info, ui->openglwidget->save_scale);
    }
    ui->openglwidget->update();
  }
}

void MainWindow::on_yRotSlider_valueChanged(int value) {
  ui->xRotSlider->setValue(0);
  ui->zRotSlider->setValue(0);
  if (ui->openglwidget->is_data_parsed) {
    copy_data(ui->openglwidget->info, ui->openglwidget->buff_info);
    rotation_by_oy(ui->openglwidget->info, value / M_PI / 30);
    if (ui->openglwidget->save_move_x != 0) {
      move_x(ui->openglwidget->info, ui->openglwidget->save_move_x);
    }
    if (ui->openglwidget->save_move_y != 0) {
      move_y(ui->openglwidget->info, ui->openglwidget->save_move_y);
    }
    if (ui->openglwidget->save_move_z != 0) {
      move_z(ui->openglwidget->info, ui->openglwidget->save_move_z);
    }
    if (ui->openglwidget->save_scale != 0) {
      scaling(ui->openglwidget->info, ui->openglwidget->save_scale);
    }
    ui->openglwidget->update();
  }
}

void MainWindow::on_zRotSlider_valueChanged(int value) {
  ui->xRotSlider->setValue(0);
  ui->yRotSlider->setValue(0);
  if (ui->openglwidget->is_data_parsed) {
    copy_data(ui->openglwidget->info, ui->openglwidget->buff_info);
    rotation_by_oz(ui->openglwidget->info, value / M_PI / 30);
    if (ui->openglwidget->save_move_x != 0) {
      move_x(ui->openglwidget->info, ui->openglwidget->save_move_x);
    }
    if (ui->openglwidget->save_move_y != 0) {
      move_y(ui->openglwidget->info, ui->openglwidget->save_move_y);
    }
    if (ui->openglwidget->save_move_z != 0) {
      move_z(ui->openglwidget->info, ui->openglwidget->save_move_z);
    }
    if (ui->openglwidget->save_scale != 0) {
      scaling(ui->openglwidget->info, ui->openglwidget->save_scale);
    }
    ui->openglwidget->update();
  }
}

void MainWindow::on_scaleSlider_valueChanged(int value) {
  if (ui->openglwidget->is_data_parsed) {
    copy_data(ui->openglwidget->info, ui->openglwidget->buff_info);
    if (value != 0) {
      if (value > 0) {
        scaling(ui->openglwidget->info, ((double)value));
        ui->openglwidget->save_scale = ((double)value);
      } else {
        value *= -1;
        scaling(ui->openglwidget->info, 1 / ((double)value));
        ui->openglwidget->save_scale = 1 / ((double)value);
      }
    }
    if (ui->openglwidget->save_move_x != 0) {
      move_x(ui->openglwidget->info, ui->openglwidget->save_move_x);
    }
    if (ui->openglwidget->save_move_y != 0) {
      move_y(ui->openglwidget->info, ui->openglwidget->save_move_y);
    }
    if (ui->openglwidget->save_move_z != 0) {
      move_z(ui->openglwidget->info, ui->openglwidget->save_move_z);
    }
    ui->openglwidget->update();
  }
}

void MainWindow::on_xTransSlider_valueChanged(int value) {
  if (ui->openglwidget->is_data_parsed) {
    copy_data(ui->openglwidget->info, ui->openglwidget->buff_info);
    move_x(ui->openglwidget->info, value / 20);
    ui->openglwidget->save_move_x = value / 20;
    if (ui->openglwidget->save_move_y != 0) {
      move_y(ui->openglwidget->info, ui->openglwidget->save_move_y);
    }
    if (ui->openglwidget->save_move_z != 0) {
      move_z(ui->openglwidget->info, ui->openglwidget->save_move_z);
    }
    if (ui->openglwidget->save_scale != 0) {
      scaling(ui->openglwidget->info, ui->openglwidget->save_scale);
    }
    ui->openglwidget->update();
  }
}

void MainWindow::on_yTransSlider_valueChanged(int value) {
  if (ui->openglwidget->is_data_parsed) {
    copy_data(ui->openglwidget->info, ui->openglwidget->buff_info);
    move_y(ui->openglwidget->info, value / 20);
    ui->openglwidget->save_move_y = value / 20;
    if (ui->openglwidget->save_move_x != 0) {
      move_x(ui->openglwidget->info, ui->openglwidget->save_move_x);
    }
    if (ui->openglwidget->save_move_z != 0) {
      move_z(ui->openglwidget->info, ui->openglwidget->save_move_z);
    }
    if (ui->openglwidget->save_scale != 0) {
      scaling(ui->openglwidget->info, ui->openglwidget->save_scale);
    }
    ui->openglwidget->update();
  }
}

void MainWindow::on_zTransSlider_valueChanged(int value) {
  if (ui->openglwidget->is_data_parsed) {
    copy_data(ui->openglwidget->info, ui->openglwidget->buff_info);
    move_z(ui->openglwidget->info, value / 20);
    ui->openglwidget->save_move_z = value / 20;
    if (ui->openglwidget->save_move_y != 0) {
      move_y(ui->openglwidget->info, ui->openglwidget->save_move_y);
    }
    if (ui->openglwidget->save_move_x != 0) {
      move_x(ui->openglwidget->info, ui->openglwidget->save_move_x);
    }
    if (ui->openglwidget->save_scale != 0) {
      scaling(ui->openglwidget->info, ui->openglwidget->save_scale);
    }
    ui->openglwidget->update();
  }
}

void MainWindow::on_imageButton_clicked() {
  if (ui->openglwidget->is_data_parsed) {
    QFileDialog dialogConnectImage(this);
    QDateTime current_date = QDateTime::currentDateTime();
    QString formattedTime = current_date.toString("yyyy-MM-dd hh.mm.ss");
    QString name_pattern = "Screen Shot " + formattedTime + ".jpeg";
    QString image_name = dialogConnectImage.getSaveFileName(
        this, tr("Save a screenshot"), name_pattern,
        tr("image (*.jpeg *.bmp)"));
    if (image_name.length() >= 1) {
      QImage img = ui->openglwidget->grabFramebuffer();
      img.save(image_name);
      QMessageBox messageBoxImage;
      messageBoxImage.information(0, "", "Screenshot saved successfully");
    }
  } else {
    msg.showMessage("Please open the file to take a screenshot!\n");
  }
}

void MainWindow::on_gifButton_clicked() {
  if (ui->openglwidget->is_data_parsed) {
    QDateTime current_date = QDateTime::currentDateTime();
    QString formattedTime = current_date.toString("yyyy-MM-dd hh.mm.ss");

    QString name_pattern = "Screen Cast " + formattedTime + ".gif";
    gif_name = QFileDialog::getSaveFileName(this, tr("Save a gif animation"),
                                            name_pattern, tr("gif (*.gif)"));
    if (gif_name != "") {
      ui->gifButton->setDisabled(true);
      gif_frame = new QGifImage;
      gif_frame->setDefaultDelay(10);
      timer->setInterval(100);
      timer->start();
    }
  } else {
    msg.showMessage("Please open .obj file to make a gif");
  }
}

void MainWindow::make_gif() {
  QImage image = ui->openglwidget->grabFramebuffer();
  QSize image_size(640, 480);
  QImage scaled_image = image.scaled(image_size);
  gif_frame->addFrame(scaled_image);
  if (frames_counter == 50) {
    timer->stop();
    gif_frame->save(gif_name);
    frames_counter = 0;
    QMessageBox messageBoxGif;
    messageBoxGif.information(0, "", "Gif saved successfully!");
    delete gif_frame;
    ui->gifButton->setText("");
    ui->gifButton->setEnabled(true);
  }
  frames_counter++;
}

void MainWindow::on_BgColorButton_clicked() {
  bgColor = QColorDialog::getColor(bgColor, this);
  if (bgColor.isValid()) {
    ui->openglwidget->setBackgroundColor(bgColor);
  }
}

void MainWindow::saveSettings() {
  QSettings settings("MyCompany", "MyApp");
  settings.setValue("backgroundColor", ui->openglwidget->getBackgroundColor());
  settings.setValue("lineStyle", (int)ui->openglwidget->currentLineStyle);
  settings.setValue("thickness", ui->openglwidget->thickness);
  settings.setValue("edgeColor", ui->openglwidget->edgeColor);
  settings.setValue("vertexColor", ui->openglwidget->vertexColor);
  settings.setValue("vertexStyle", ui->openglwidget->currentVertexStyle);
  settings.setValue("thickness_of_vertexes",
                    ui->openglwidget->thickness_of_vertexes);
  settings.setValue("projection", ui->openglwidget->currentProjectionType);
}
