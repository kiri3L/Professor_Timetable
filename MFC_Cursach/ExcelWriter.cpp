#include "stdafx.h"
#include "ExcelWriter.h"

ExcelWriter::ExcelWriter(std::string way1, Excel::_ApplicationPtr pApp1)
{
	way = way1.c_str();
	pApp = pApp1;//память не утекает?
	newFile = pApp->Workbooks->Add();
	Sheet = newFile->Worksheets->Item[1];

	pApp->PutVisible(0, FALSE);
	pApp->PutDisplayAlerts(0, FALSE);//отключить уведомления
}

void ExcelWriter::writeCell(int strok, int stolb, std::string text, bool color)
{
	Excel::RangePtr cell = Sheet->Cells->Item[strok][stolb];
	bstr_t a = text.c_str();
	cell->Value2 = a;
	if (color)
	{
		cell->Interior->Color = Excel::rgbRed; //красим фон
		cell->Font->Color = Excel::rgbWhite; //красим текст
	}
}

void ExcelWriter::shablon(int teachNumb)
{
	Excel::RangePtr rows;
	Excel::RangePtr colums;
	Excel::RangePtr myRange;

	//предустановка 
	Sheet->Cells->Font->Name = "Times New Roman";
	Sheet->Cells->Font->Size = 18;
	Sheet->Cells->HorizontalAlignment = 3;
	Sheet->Cells->VerticalAlignment = 2;
	Sheet->Cells->NumberFormat = "@"; //текстовой формат ячеек
	Sheet->Rows->RowHeight = 57.75;
	myRange = Sheet->Range[Sheet->Rows->Item[3]][Sheet->Rows->Item[74]];
	myRange->AutoFit();
	//граница ячеек
	myRange = Sheet->Range[Sheet->Cells->Item[1][1]][Sheet->Cells->Item[74][5]];
	myRange->Borders->Weight = Excel::xlThin;

	//некое кол-во роус будет предустановалено по высоте, а коламс будут предустонавливаться в зависимости от кол-ва учителей
	rows = Sheet->Rows->Item[1];
	rows->RowHeight = 45;
	rows = Sheet->Rows->Item[2];
	rows->RowHeight = 69;

	//заморозка ячеек
	pApp->ActiveWindow->SplitColumn = 5;
	pApp->ActiveWindow->SplitRow = 2;
	pApp->ActiveWindow->FreezePanes = true;
	{
		//прорисовка плашки с днем недели 
		colums = Sheet->Columns->Item[1];
		colums->ColumnWidth = 4.43;
		colums->Orientation = 90;

		myRange = Sheet->Range[Sheet->Cells->Item[1][1]][Sheet->Cells->Item[2][1]];
		myRange->Merge();
		myRange->Interior->Color = RGB(255, 204, 153);
		myRange->Value2 = "День недели";
		//myRange->Borders->

		myRange = Sheet->Range[Sheet->Cells->Item[3][1]][Sheet->Cells->Item[14][1]];
		myRange->Merge();
		myRange->Interior->Color = RGB(255, 153, 204);
		myRange->Value2 = "Понедельник";

		myRange = Sheet->Range[Sheet->Cells->Item[15][1]][Sheet->Cells->Item[26][1]];
		myRange->Merge();
		myRange->Interior->Color = RGB(255, 204, 0);
		myRange->Value2 = "Вторник";

		myRange = Sheet->Range[Sheet->Cells->Item[27][1]][Sheet->Cells->Item[38][1]];
		myRange->Merge();
		myRange->Interior->Color = RGB(153, 204, 0);
		myRange->Value2 = "Среда";

		myRange = Sheet->Range[Sheet->Cells->Item[39][1]][Sheet->Cells->Item[50][1]];
		myRange->Merge();
		myRange->Interior->Color = RGB(255, 102, 0);
		myRange->Value2 = "Четверг";

		myRange = Sheet->Range[Sheet->Cells->Item[51][1]][Sheet->Cells->Item[62][1]];
		myRange->Merge();
		myRange->Interior->Color = RGB(153, 204, 255);
		myRange->Value2 = "Пятница";

		myRange = Sheet->Range[Sheet->Cells->Item[63][1]][Sheet->Cells->Item[74][1]];
		myRange->Merge();
		myRange->Interior->Color = RGB(204, 153, 255);
		myRange->Value2 = "Суббота";

		//плашка с ФИО и тд
		colums = Sheet->Columns->Item[2];
		colums->ColumnWidth = 4.14;
		colums = Sheet->Columns->Item[3];
		colums->ColumnWidth = 10.29;
		colums = Sheet->Columns->Item[4];
		colums->ColumnWidth = 9.57;
		colums = Sheet->Columns->Item[5];
		colums->ColumnWidth = 3.86;

		myRange = Sheet->Cells->Item[2][2];
		myRange->Interior->Color = RGB(255, 204, 153);
		myRange->Value2 = "№ пары";
		myRange->Orientation = 90;

		myRange = Sheet->Cells->Item[2][3];
		myRange->Interior->Color = RGB(255, 204, 153);
		myRange->Value2 = "Нач.\nзанятий";
		myRange->Orientation = 90;

		myRange = Sheet->Cells->Item[2][4];
		myRange->Interior->Color = RGB(255, 204, 153);
		myRange->Value2 = "Оконч.\nзанятий";
		myRange->Orientation = 90;

		myRange = Sheet->Cells->Item[2][5];
		myRange->Interior->Color = RGB(255, 204, 153);
		myRange->Value2 = "Неделя";
		myRange->Orientation = 90;

		myRange = Sheet->Range[Sheet->Cells->Item[1][2]][Sheet->Cells->Item[1][5]];
		myRange->Merge();
		myRange->Interior->Color = RGB(255, 204, 153);
		myRange->Value2 = "ФИО учителя";

		//плашка со временем
		for (int j = 0; j < 6; j++)
		{
			int offseat = j * 12;
			for (int k = 0; k < 12; k += 2)
			{
				//цифры в номере занятий
				myRange = Sheet->Range[Sheet->Cells->Item[3 + k + offseat][2]][Sheet->Cells->Item[4 + k + offseat][2]];
				myRange->Merge();
				myRange->Interior->Color = RGB(255, 204, 153);
				myRange->Value2 = k / 2 + 1;
			}
			//начало занятий
			myRange = Sheet->Range[Sheet->Cells->Item[3 + offseat][3]][Sheet->Cells->Item[4 + offseat][3]];
			myRange->Merge();
			myRange->Interior->Color = RGB(255, 204, 153);
			myRange->Value2 = "9-00";

			myRange = Sheet->Range[Sheet->Cells->Item[5 + offseat][3]][Sheet->Cells->Item[6 + offseat][3]];
			myRange->Merge();
			myRange->Interior->Color = RGB(255, 204, 153);
			myRange->Value2 = "10-40";

			myRange = Sheet->Range[Sheet->Cells->Item[7 + offseat][3]][Sheet->Cells->Item[8 + offseat][3]];
			myRange->Merge();
			myRange->Interior->Color = RGB(255, 204, 153);
			myRange->Value2 = "13-00";

			myRange = Sheet->Range[Sheet->Cells->Item[9 + offseat][3]][Sheet->Cells->Item[10 + offseat][3]];
			myRange->Merge();
			myRange->Interior->Color = RGB(255, 204, 153);
			myRange->Value2 = "14-40";

			myRange = Sheet->Range[Sheet->Cells->Item[11 + offseat][3]][Sheet->Cells->Item[12 + offseat][3]];
			myRange->Merge();
			myRange->Interior->Color = RGB(255, 204, 153);
			myRange->Value2 = "16-20";

			myRange = Sheet->Range[Sheet->Cells->Item[13 + offseat][3]][Sheet->Cells->Item[14 + offseat][3]];
			myRange->Merge();
			myRange->Interior->Color = RGB(255, 204, 153);
			myRange->Value2 = "18-00";

			//КОНЕЦ ЗАНЯТИЙ
			myRange = Sheet->Range[Sheet->Cells->Item[3 + offseat][4]][Sheet->Cells->Item[4 + offseat][4]];
			myRange->Merge();
			myRange->Interior->Color = RGB(255, 204, 153);
			myRange->Value2 = "10-30";

			myRange = Sheet->Range[Sheet->Cells->Item[5 + offseat][4]][Sheet->Cells->Item[6 + offseat][4]];
			myRange->Merge();
			myRange->Interior->Color = RGB(255, 204, 153);
			myRange->Value2 = "12-10";

			myRange = Sheet->Range[Sheet->Cells->Item[7 + offseat][4]][Sheet->Cells->Item[8 + offseat][4]];
			myRange->Merge();
			myRange->Interior->Color = RGB(255, 204, 153);
			myRange->Value2 = "14-30";

			myRange = Sheet->Range[Sheet->Cells->Item[9 + offseat][4]][Sheet->Cells->Item[10 + offseat][4]];
			myRange->Merge();
			myRange->Interior->Color = RGB(255, 204, 153);
			myRange->Value2 = "16-10";

			myRange = Sheet->Range[Sheet->Cells->Item[11 + offseat][4]][Sheet->Cells->Item[12 + offseat][4]];
			myRange->Merge();
			myRange->Interior->Color = RGB(255, 204, 153);
			myRange->Value2 = "17-50";

			myRange = Sheet->Range[Sheet->Cells->Item[13 + offseat][4]][Sheet->Cells->Item[14 + offseat][4]];
			myRange->Merge();
			myRange->Interior->Color = RGB(255, 204, 153);
			myRange->Value2 = "19-30";

			//НЕДЕЛЯ
			for (int week = 0; week < 12; week += 2)
			{
				myRange = Sheet->Cells->Item[3 + week + offseat][5];
				myRange->Interior->Color = RGB(255, 204, 153);
				myRange->Value2 = "I";

				myRange = Sheet->Cells->Item[4 + week + offseat][5];
				myRange->Interior->Color = RGB(255, 204, 153);
				myRange->Value2 = "II";
			}
		}
	}

	for (int i = 0; i < teachNumb; i++)
	{
		int offseat2 = i*5;
		myRange = Sheet->Cells->Item[1][6 + offseat2];
		myRange->Font->Size = 28;
		myRange->Font->Bold = true;
		//границы
		myRange = Sheet->Range[Sheet->Cells->Item[1][6 + offseat2]][Sheet->Cells->Item[74][10 + offseat2]];
		myRange->Borders->Weight = Excel::xlThin;
		myRange->Borders->Color = RGB(0, 0, 0);
		myRange->Borders->Item[Excel::xlEdgeRight]->Weight = Excel::xlThick;			
		myRange->Borders->Item[Excel::xlEdgeBottom]->Weight = Excel::xlThick;
		for (int j = 0; j < 6; j++)
		{
			int offseat = j * 12;
			myRange = Sheet->Range[Sheet->Cells->Item[3+offseat][6 + offseat2]][Sheet->Cells->Item[3+offseat][10 + offseat2]];
			myRange->Borders->Item[Excel::xlEdgeTop]->Weight = Excel::xlThick;
		}

		//плашка верхняя
		colums = Sheet->Columns->Item[6 + offseat2];
		colums->ColumnWidth = 48.29;
		colums = Sheet->Columns->Item[7 + offseat2];
		colums->ColumnWidth = 6.57;
		colums = Sheet->Columns->Item[8 + offseat2];
		colums->ColumnWidth = 23.86;
		colums = Sheet->Columns->Item[9 + offseat2];
		colums->ColumnWidth = 13.57;
		colums = Sheet->Columns->Item[10 + offseat2];
		colums->ColumnWidth = 15.29;

		myRange = Sheet->Range[Sheet->Cells->Item[1][9 + offseat2]][Sheet->Cells->Item[74][10 + offseat2]];
		myRange->Interior->Color = RGB(255, 204, 153);

		myRange = Sheet->Range[Sheet->Cells->Item[1][6 + offseat2]][Sheet->Cells->Item[1][8 + offseat2]];
		myRange->Merge();
		myRange->Interior->Color = RGB(153,255,153);

		myRange = Sheet->Cells->Item[2][6 + offseat2];
		myRange->Value2 = "Предмет";
		myRange->Interior->Color = RGB(255, 204, 153);
		myRange = Sheet->Cells->Item[2][7 + offseat2];
		myRange->Value2 = "Вид\nзанятий";
		myRange->Interior->Color = RGB(255, 204, 153);
		myRange->Orientation = 90;
		myRange = Sheet->Cells->Item[2][8 + offseat2];
		myRange->Value2 = "Группа";
		myRange->Interior->Color = RGB(255, 204, 153);
		myRange = Sheet->Cells->Item[2][9 + offseat2];
		myRange->Value2 = "№ \nауд.";
		myRange = Sheet->Cells->Item[2][10 + offseat2];
		myRange->Value2 = "Число \nстудентов";
	}
}

ExcelWriter::~ExcelWriter()
{
//	pApp->PutDisplayAlerts(0, true);//отключить уведомления
	way = pApp->GetSaveAsFilename();
	way += "xlsx";
	newFile->SaveAs(way, Excel::xlWorkbookDefault, "", "", FALSE, FALSE, Excel::XlSaveAsAccessMode::xlNoChange); //сохранение книги по адресу
	way += " - файл создан;";
	MessageBox(NULL, way, L" ", MB_OK | MB_ICONINFORMATION);
}
