#ifndef SIGNALSLOTSAMPLE_H
#define SIGNALSLOTSAMPLE_H

#include <QtWidgets/QMainWindow>
#include "ui_signalslotsample.h"

class SignalSlotSample : public QMainWindow
{
	Q_OBJECT

public:
	SignalSlotSample(QWidget *parent = 0);
	~SignalSlotSample();

private:
	Ui::SignalSlotSampleClass ui;
};

#endif // SIGNALSLOTSAMPLE_H
