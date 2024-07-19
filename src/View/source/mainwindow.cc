#include "mainwindow.h"

#include "./ui_mainwindow.h"

using namespace s21;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->controller = new s21::Controller();
  ui->openglwidget->setController(this->controller);
  QSettings settings("School 21", "3DViewer");
  controller->setBackgroundColorR(settings.value("backgroundColorR").toFloat());
  controller->setBackgroundColorG(settings.value("backgroundColorG").toFloat());
  controller->setBackgroundColorB(settings.value("backgroundColorB").toFloat());
  controller->setEdgeColorR(settings.value("edgeColorR").toFloat());
  controller->setEdgeColorG(settings.value("edgeColorG").toFloat());
  controller->setEdgeColorB(settings.value("edgeColorB").toFloat());
  controller->setVertexColorR(settings.value("vertexColorR").toFloat());
  controller->setVertexColorG(settings.value("vertexColorG").toFloat());
  controller->setVertexColorB(settings.value("vertexColorB").toFloat());
  controller->setEdgeStyle((EdgeStyle)settings.value("edgeStyle").toInt());
  controller->setVertexStyle(
      (VertexStyle)settings.value("vertexStyle").toInt());
  controller->setProjectionType(
      (ProjectionType)settings.value("projectionType").toInt());
  controller->setThickness(settings.value("thickness").toFloat());
  controller->setThicknessOfVertices(
      settings.value("thicknessOfVertices").toFloat());
  timer = new QTimer(0);
  connect(timer, SIGNAL(timeout()), this, SLOT(makeGif()));
  framesCounter = 0;
}

MainWindow::~MainWindow() {
  isParsed = false;
  ui->openglwidget->setIsParsed(isParsed);
  saveSettings();
  delete controller;
  delete ui;
}

void MainWindow::on_openButton_clicked() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open .obj file:"), "~/", tr("Obj Files (*.obj)"));
  if (!filename.isEmpty() && !filename.isNull()) {
    QStringList pieces = filename.split("/");
    QString filenameWithoutPath = pieces.value(pieces.length() - 1);
    ui->fileNameLabel->setText(filenameWithoutPath);
    ui->filePathLabel->setText(filename);
    parseObj(filename);
    if (isParsed) {
      ui->xRotSlider->setValue(0);
      ui->yRotSlider->setValue(0);
      ui->zRotSlider->setValue(0);
      ui->xTransSlider->setValue(0);
      ui->yTransSlider->setValue(0);
      ui->zTransSlider->setValue(0);
      ui->scaleSlider->setValue(0);
    }
    ui->verticesCountLabel->setText(
        QString::number(controller->getCountOfVertices()));
    ui->edgesCountLabel->setText(
        QString::number(controller->getCountOfFacets()));
  } else {
    msg.showMessage("Please open the file to view the image!\n");
  }
}

void MainWindow::parseObj(const QString filename) {
  controller->setModel();
  isParsed = false;
  ui->openglwidget->setIsParsed(isParsed);
  char str[filename.length()];
  fromQStrToString(str, filename);
  FILE *objFile = fopen(str, "r");
  if (objFile != nullptr) {
    controller->runParsingObj(objFile);
    isParsed = true;
  } else {
    msg.showMessage("File not opened!\n");
  }
  fclose(objFile);
  resetSettings();
  ui->openglwidget->setIsParsed(isParsed);
}

void MainWindow::fromQStrToString(char *str, const QString qstr) const {
  for (int i = 0; i < qstr.length(); ++i) {
    str[i] = qstr.toStdString().c_str()[i];
  }
  str[qstr.length()] = '\0';
}

void MainWindow::resetSettings() const {
  ui->xRotSlider->setValue(0);
  ui->yRotSlider->setValue(0);
  ui->zRotSlider->setValue(0);
  ui->xTransSlider->setValue(0);
  ui->yTransSlider->setValue(0);
  ui->zTransSlider->setValue(0);
  ui->scaleSlider->setValue(0);
}

void MainWindow::on_scaleSlider_valueChanged(int value) {
  if (isParsed) {
    ui->xRotSlider->setValue(0);
    ui->yRotSlider->setValue(0);
    ui->zRotSlider->setValue(0);
    ui->xTransSlider->setValue(0);
    ui->yTransSlider->setValue(0);
    ui->zTransSlider->setValue(0);
    s21::Scale scale(controller);
    contextStrategy.setStrategy(&scale);
    contextStrategy.transform(value);
    ui->openglwidget->update();
  }
}

void MainWindow::on_xTransSlider_valueChanged(int value) {
  if (isParsed) {
    ui->xRotSlider->setValue(0);
    ui->yRotSlider->setValue(0);
    ui->zRotSlider->setValue(0);
    ui->yTransSlider->setValue(0);
    ui->zTransSlider->setValue(0);
    ui->scaleSlider->setValue(0);
    s21::TranslationX translationX(controller);
    contextStrategy.setStrategy(&translationX);
    contextStrategy.transform(value);
    ui->openglwidget->update();
  }
}

void MainWindow::on_yTransSlider_valueChanged(int value) {
  if (isParsed) {
    ui->xRotSlider->setValue(0);
    ui->yRotSlider->setValue(0);
    ui->zRotSlider->setValue(0);
    ui->xTransSlider->setValue(0);
    ui->zTransSlider->setValue(0);
    ui->scaleSlider->setValue(0);
    s21::TranslationY translationY(controller);
    contextStrategy.setStrategy(&translationY);
    contextStrategy.transform(value);
    ui->openglwidget->update();
  }
}

void MainWindow::on_zTransSlider_valueChanged(int value) {
  if (isParsed) {
    ui->xRotSlider->setValue(0);
    ui->yRotSlider->setValue(0);
    ui->zRotSlider->setValue(0);
    ui->xTransSlider->setValue(0);
    ui->yTransSlider->setValue(0);
    ui->scaleSlider->setValue(0);
    s21::TranslationZ translationZ(controller);
    contextStrategy.setStrategy(&translationZ);
    contextStrategy.transform(value);
    ui->openglwidget->update();
  }
}

void MainWindow::on_xRotSlider_valueChanged(int value) {
  if (isParsed) {
    ui->yRotSlider->setValue(0);
    ui->zRotSlider->setValue(0);
    ui->xTransSlider->setValue(0);
    ui->yTransSlider->setValue(0);
    ui->zTransSlider->setValue(0);
    ui->scaleSlider->setValue(0);
    s21::RotateX rotateX(controller);
    contextStrategy.setStrategy(&rotateX);
    contextStrategy.transform(value);
    ui->openglwidget->update();
  }
}

void MainWindow::on_yRotSlider_valueChanged(int value) {
  if (isParsed) {
    ui->xRotSlider->setValue(0);
    ui->zRotSlider->setValue(0);
    ui->xTransSlider->setValue(0);
    ui->yTransSlider->setValue(0);
    ui->zTransSlider->setValue(0);
    ui->scaleSlider->setValue(0);
    s21::RotateY rotateY(controller);
    contextStrategy.setStrategy(&rotateY);
    contextStrategy.transform(value);
    ui->openglwidget->update();
  }
}

void MainWindow::on_zRotSlider_valueChanged(int value) {
  if (isParsed) {
    ui->xRotSlider->setValue(0);
    ui->yRotSlider->setValue(0);
    ui->xTransSlider->setValue(0);
    ui->yTransSlider->setValue(0);
    ui->zTransSlider->setValue(0);
    ui->scaleSlider->setValue(0);
    s21::RotateZ rotateZ(controller);
    contextStrategy.setStrategy(&rotateZ);
    contextStrategy.transform(value);
    ui->openglwidget->update();
  }
}

void MainWindow::on_edgeThickness_valueChanged(int value) {
  if (isParsed) {
    ui->openglwidget->setThickness(value / 20.0f);
    ui->openglwidget->update();
  }
}

void MainWindow::on_vertexThickness_valueChanged(int value) {
  if (isParsed) {
    ui->openglwidget->setThicknessOfVertices(value);
    ui->openglwidget->update();
  }
}

void MainWindow::on_solidButton_toggled(bool checked) {
  if (isParsed && checked) {
    ui->openglwidget->setEdgeStyle(SOLID);
    ui->openglwidget->update();
  }
}

void MainWindow::on_dashButton_toggled(bool checked) {
  if (isParsed && checked) {
    ui->openglwidget->setEdgeStyle(DASHED);
    ui->openglwidget->update();
  }
}

void MainWindow::on_circleButton_toggled(bool checked) {
  if (isParsed && checked) {
    ui->openglwidget->setVertexStyle(CIRCLE);
    ui->openglwidget->update();
  }
}

void MainWindow::on_squareButton_toggled(bool checked) {
  if (isParsed && checked) {
    ui->openglwidget->setVertexStyle(SQUARE);
    ui->openglwidget->update();
  }
}

void MainWindow::on_noneButton_toggled(bool checked) {
  if (isParsed && checked) {
    ui->openglwidget->setVertexStyle(NONE);
    ui->openglwidget->update();
  }
}

void MainWindow::on_BgColorButton_clicked() {
  if (isParsed) {
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
      ui->openglwidget->setBackgroundColor(color);
    }
  } else {
    msg.showMessage("Please open the file to change a color!\n");
  }
}

void MainWindow::on_vertexColor_clicked() {
  if (isParsed) {
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
      ui->openglwidget->setVertexColor(color);
    }
  } else {
    msg.showMessage("Please open the file to change a color!\n");
  }
}

void MainWindow::on_edgeColor_clicked() {
  if (isParsed) {
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
      ui->openglwidget->setEdgeColor(color);
    }
  } else {
    msg.showMessage("Please open the file to change a color!\n");
  }
}

void MainWindow::on_centralButton_toggled(bool checked) {
  if (isParsed && checked) {
    ui->openglwidget->setProjectionType(CENTRAL);
    ui->openglwidget->update();
  }
}

void MainWindow::on_parallelButton_toggled(bool checked) {
  if (isParsed && checked) {
    ui->openglwidget->setProjectionType(PARALLEL);
    ui->openglwidget->update();
  }
}

void MainWindow::on_imageButton_clicked() {
  if (isParsed) {
    QFileDialog dialogConnectImage(this);
    QDateTime currentDate = QDateTime::currentDateTime();
    QString formattedTime = currentDate.toString("yyyy-MM-dd hh.mm.ss");
    QString namePattern = "Screen Shot " + formattedTime + ".jpeg";
    QString imageName = dialogConnectImage.getSaveFileName(
        this, tr("Save a screenshot"), namePattern, tr("image (*.jpeg *.bmp)"));
    if (imageName.length() >= 1) {
      QImage img = ui->openglwidget->grabFramebuffer();
      img.save(imageName);
      QMessageBox messageBoxImage;
      messageBoxImage.information(0, "", "Screenshot saved successfully");
    }
  } else {
    msg.showMessage("Please open the file to take a screenshot!\n");
  }
}

void MainWindow::on_gifButton_clicked() {
  if (isParsed) {
    QDateTime currentDate = QDateTime::currentDateTime();
    QString formattedTime = currentDate.toString("yyyy-MM-dd hh.mm.ss");
    QString namePattern = "Screen Cast " + formattedTime + ".gif";
    gifName = QFileDialog::getSaveFileName(this, tr("Save a gif animation"),
                                           namePattern, tr("gif (*.gif)"));
    if (gifName != "") {
      ui->gifButton->setDisabled(true);
      gifFrame = new QGifImage;
      gifFrame->setDefaultDelay(10);
      timer->setInterval(100);
      timer->start();
    }
  } else {
    msg.showMessage("Please open .obj file to make a gif");
  }
}

void MainWindow::makeGif() {
  QImage image = ui->openglwidget->grabFramebuffer();
  QSize imageSize(640, 480);
  QImage scaledImage = image.scaled(imageSize);
  gifFrame->addFrame(scaledImage);
  if (framesCounter == 50) {
    timer->stop();
    gifFrame->save(gifName);
    framesCounter = 0;
    QMessageBox messageBoxGif;
    messageBoxGif.information(0, "", "Gif saved successfully!");
    delete gifFrame;
    ui->gifButton->setText("");
    ui->gifButton->setEnabled(true);
  }
  framesCounter++;
}

void MainWindow::saveSettings() const {
  QSettings settings("School 21", "3DViewer");
  settings.setValue("backgroundColorR", controller->getBackgroundColorR());
  settings.setValue("backgroundColorG", controller->getBackgroundColorG());
  settings.setValue("backgroundColorB", controller->getBackgroundColorB());
  settings.setValue("edgeColorR", controller->getEdgeColorR());
  settings.setValue("edgeColorG", controller->getEdgeColorG());
  settings.setValue("edgeColorB", controller->getEdgeColorB());
  settings.setValue("vertexColorR", controller->getVertexColorR());
  settings.setValue("vertexColorG", controller->getVertexColorG());
  settings.setValue("vertexColorB", controller->getVertexColorB());
  settings.setValue("edgeStyle", controller->getEdgeStyle());
  settings.setValue("vertexStyle", controller->getVertexStyle());
  settings.setValue("projectionType", controller->getProjectionType());
  settings.setValue("thickness", controller->getThickness());
  settings.setValue("thicknessOfVertices",
                    controller->getThicknessOfVertices());
}
