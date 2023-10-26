#ifndef STYLES_H
#define STYLES_H

#define styleSheet \
  "QPushButton { \
                      background-color: rgb(170, 170, 255); \
                      border: 2px  solid  rgb(0, 170, 255); \
                      border-radius: 8px; \
                      color: white;    \
} \
\
QPushButton:hover { \
  background-color:  rgb(0, 255, 255); \
} \
\
QPushButton:pressed { \
  margin-top: 5px; \
  margin-right: 5px; \
  margin-left: 5px; \
  background-color: rgb(214, 249, 86); \
} \
QFrame { \
  color: white; \
  margin-top: 5px; \
  border: 1px solid white; \
  border-radius: 15px; \
} \
\
QLabel { \
  margin-top: 0; \
  border: none; \
}"
#endif  // STYLES_H
