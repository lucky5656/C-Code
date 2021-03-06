#include"student.h"

//默认构造
Student::Student()
{

}

//有参构造（参数：学号、姓名、密码）
Student::Student(int id, string name, string pwd)
{
	//初始化属性
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		vCom.push_back(com);  //将读取的信息放入到容器中
	}
	ifs.close();
}

//菜单界面
void Student::operMenu()
{
	cout << "欢迎学生代表：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.申请预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.查看我的预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.取消预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//申请预约
void Student::applyOrder()
{
	cout << "机房开放的时间为周一至周五！" << endl;
	cout << "请选择申请预约的时间：" << endl;
	cout << "1. 周一" << "  2. 周二" << "  3. 周三" << "  4. 周四" << "  5. 周五" << endl;

	int date = 0;  //日期
	int interval = 0;  //时间段
	int room = 0;  //机房编号

	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		else
		{
			cout << "输入有误，请重新输入：" << endl;
		}
	}

	cout << "请选择申请预约的时间段：" << endl;
	cout << "1. 上午（8:00 - 12:00）" << "  2. 下午（14:00 - 18:00）" << endl;

	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		else
		{
			cout << "输入有误，请重新输入：" << endl;
		}
	}

	cout << "请选择机房：" << endl;
	for (int i = 0; i < vCom.size(); i++)
	{
		cout << vCom[i].m_ComId << "号机房的容量为：" << vCom[i].m_MaxNum << endl;
	}

	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		else
		{
			cout << "输入有误，请重新输入：" << endl;
		}
	}

	cout << "预约成功！审核中..." << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);

	ofs << "date:" << date << " ";  //日期
	ofs << "interval:" << interval << " ";  //时间段
	ofs << "stuId:" << this->m_Id << " ";  //学生学号
	ofs << "stuName:" << this->m_Name << " ";  //学生姓名
	ofs << "roomId:" << room << " ";  //机房编号
	ofs << "status:" << 1 << " ";  //预约状态（1代表审核中）

	ofs.close();

	system("pause");
	system("cls");
}

//查看自身预约
void Student::showMyOrder()
{
	OrderFile of;

	if (of.m_Size == 0)  //无预约记录，返回
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	//有预约记录，将自身信息返回
	for (int i = 0; i < of.m_Size; i++)
	{
		//找到自身预约
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)  //.c_str()将string转化为const char *；atoi()将const char *转化为int；整体就是将string转为int
		{
			cout << "预约日期：周" << of.m_orderData[i]["date"];
			cout << "    时间段：" << (of.m_orderData[i]["interval"]=="1"?"上午":"下午");
			cout << "    机房编号：" << of.m_orderData[i]["roomId"];
			string status = "    预约状态：";
			//1 审核中；2 已预约；-1 预约失败；0 取消预约
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "审核中...";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "审核通过，预约成功！";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "审核未通过，预约失败！";
			}
			else if (of.m_orderData[i]["status"] == "0")
			{
				status += "取消预约！";
			}
			cout << status << endl;
		}
	}
	system("pause");
	system("cls");
}

//查看所有预约
void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "、 ";
		cout << "预约日期：周" << of.m_orderData[i]["date"];
		cout << "    时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << "    学号：" << of.m_orderData[i]["stuId"];
		cout << "    姓名：" << of.m_orderData[i]["stuName"];
		cout << "    机房编号：" << of.m_orderData[i]["roomId"];
		string status = "    预约状态：";
		//1 审核中；2 已预约；-1 预约失败；0 取消预约
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中...";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "审核通过，预约成功！";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "审核未通过，预约失败！";
		}
		else if (of.m_orderData[i]["status"] == "0")
		{
			status += "取消预约！";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

//取消预约
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}


	cout << "审核中或预约成功的记录可以取消，您的预约记录如下：" << endl;
	vector<int>v;  //存放最大容器中的下标编号
	int index = 1;    //提示用户需要操作的预约记录的条数
	for (int i = 0; i < of.m_Size; i++)
	{
		//先判断是否是自身学号
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			//再筛选状态，审核中或预约成功
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、 ";
				cout << "预约日期：周" << of.m_orderData[i]["date"];
				cout << "    时间段：" << (of.m_orderData[i]["interval"] == "1"?"上午":"下午");
				cout << "    机房编号：" << of.m_orderData[i]["roomId"];

				string status = "    预约状态：";
				//1 审核中；2 已预约；-1 预约失败；0 取消预约
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "审核中...";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "审核通过，预约成功！";
				}
				cout << status << endl;
			}
		}
	}

	cout << "请输入需要取消的记录（0代表返回）：" << endl;
	int select = 0;

	while (true)
	{
		cin >> select;

		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				of.m_orderData[v[select - 1]]["status"] = "0";  //v[select - 1]用于需要取消的记录所在位置

				of.updateOrder();  //更新数据

				cout << "已取消预约！" << endl;
				break;
			}
		}

		cout << "输入有误，请重新输入：" << endl;
	}

	system("pause");
	system("cls");
}