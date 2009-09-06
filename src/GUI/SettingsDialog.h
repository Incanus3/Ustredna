#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

class SettingsDialog : public QDialog
{
	Q_OBJECT

		public:
	SettingsDialog(QString path, QWidget* parent = 0);

		private slots:
	void openFile();
	void saveSettings();

		private:
	void createLayouts();
	void initializeConnections();

	QLabel* defaultDataPathLabel;
	QLineEdit* defaultDataPathEdit;
	QPushButton* openButton;
	QPushButton* applyButton;
	QPushButton* okButton;
	QPushButton* cancelButton;
};

#endif // SETTINGSDIALOG_H
