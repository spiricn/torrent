TEMPLATE = subdirs

SUBDIRS += \
    app \
    libBE \
    libBT

libBT.depends = libBE

app.depends = libBT
