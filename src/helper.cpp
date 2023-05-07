#include "include/helper.h"

#include <QFileDialog>
#include <QLineEdit>

void AOCharMaker::Helper::openFileDialog(QWidget *f_context, QLineEdit *f_line_edit)
{
    QFileDialog l_dialog(f_context, "Select animation", "", "");
    l_dialog.setFileMode(QFileDialog::ExistingFile);
    QFileDialog::connect(&l_dialog, &QFileDialog::fileSelected, f_context, [&f_line_edit](QString f_filename){
        QString l_file_name = f_filename.split("/").last().split(".").first();
        QString l_final_name = l_file_name.replace("(a)", "").replace("(b)","").replace("(c)","");
        f_line_edit->setText(l_final_name);
    });
    l_dialog.exec();
}
