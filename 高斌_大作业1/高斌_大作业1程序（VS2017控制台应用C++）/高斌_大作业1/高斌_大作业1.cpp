/*
opengl计算机图形学编程
高斌_大作业1
2021_7_2
*/
#include<Windows.h>
#include<iostream>
#include<gl/GL.h>
#include<gl/glut.h>
#include<gl/freeglut.h>
#include<cmath>
#define PI 3.1415926

/*全局变量*/
static int option_value = 1;            //菜单值
static GLfloat move = 0.0;				//平移量
static GLfloat spin = 0.0;				//旋转量
static GLfloat size = 1.0;				//缩放量
static double  sumT_Count = 0;             //平移总距离
static double  sumR_Count = 0;             //旋转总度数
static double  sumS_Count = 1;             //缩放总数
static double  speedlevel = 1;         //速度等级
static double  LINE_or_FILL = 0;            //是否填充的判断


/*绘制三角形*/
void gaobin_Triangle(void)
{
	glClearColor(0.0, 0.5, 1.0, 1.0);		//指定清除颜色，即set背景颜色
	glClear(GL_COLOR_BUFFER_BIT);		    //清除所有的像素, 清除屏幕颜色，即将屏幕的所有像素点都还原为 “底色 ”。

	/*中心点*/
	glPointSize(10.0);           //设置点大小，必须在glBegin和glEnd之外调用glPointSize()
	glBegin(GL_POINTS);
		glColor3d(1.0, 0.0, 0.0); //设置第1个点颜色
		glVertex2d(0, 0); //设置第1个点位置
	glEnd();
	glEnable(GL_POINT_SMOOTH);     //将方形点变为圆形点     

	/*是否填充*/
	if(LINE_or_FILL==0)	glPolygonMode(GL_BACK, GL_LINE);  //线框模式
	else if(LINE_or_FILL==1)glPolygonMode(GL_BACK, GL_FILL);  //填充模式

	/*三角形*/
	glLineWidth(4.0f);                // 设置线的宽度
	glBegin(GL_TRIANGLES);
	    glColor3d(0.0, 1.0, 0.0); //设置颜色
		glVertex2d(0.25*cos(0), 0.25*sin(0));
		glVertex2d(0.25*cos(240 * PI / 180), 0.25*sin(240 * PI / 180));
		glVertex2d(0.25*cos(120 * PI / 180), 0.25*sin(120 * PI / 180));
	glEnd();

	//平移模块
	if (move != 0)
	{
		sumT_Count += move * speedlevel;
		if (sumT_Count <= 1)
		{
			glTranslatef(GLfloat(move * speedlevel), 0, 0);
		}
		if (sumT_Count >= 1 && sumT_Count < 3)
		{
			glTranslatef(GLfloat(-move * speedlevel), 0, 0);
		}
		if (sumT_Count >= 3 && sumT_Count < 4)
		{
			glTranslatef(GLfloat(move* speedlevel), 0, 0);
		}
		if (sumT_Count >= 4)
		{
			move = 0;
		}
	}
	//旋转模块
	if (spin != 0)
	{
		sumR_Count += spin * speedlevel;
		if (sumR_Count <= 360)
		{
			glRotatef(GLfloat(-spin * speedlevel), 0, 0, 1);
		}
		if (sumR_Count > 360 && sumR_Count <= 720)
		{
			glRotatef(GLfloat(spin* speedlevel), 0, 0, 1);
		}
		if (sumR_Count > 720)
		{
			spin = 0;
		}
	}
	//缩放模块
	if (size != 1)
	{
		int times = 0;
		if (speedlevel == 1)times = 15;
		else if (speedlevel == 3)times = 5;
		else if(speedlevel == 5)times = 3;
	    if (sumS_Count < times)
		{
			glScalef(GLfloat(pow(size,speedlevel)), GLfloat(pow(size, speedlevel)), 1);
			sumS_Count +=1;
			Sleep(250);
		}
		if (sumS_Count>=times && sumS_Count <2*times)
		{
			glScalef(GLfloat(pow(1/size, speedlevel)), GLfloat(pow(1/size, speedlevel)),1);
			sumS_Count +=1;
			Sleep(250);
		}
		if (sumS_Count >=2*times)
		{
			size = 1;
		}
	}
	glutPostRedisplay();
	glutSwapBuffers();                        //强制刷新
}
/*变换菜单函数*/
void TransformMenu(int date)
{
	option_value = date;
	switch (option_value)
	{
	case 1://平移
		sumT_Count = 0;
		spin = 0;
		size = 1;
		move = 0.005f ;
		break;
	case 2://旋转
		sumR_Count = 0;
		move = 0;
		size = 1;
		spin = 0.5f;
		break;
	case 3://缩放
		sumS_Count = 0;
		move = 0;
		spin = 0;
		size = 1.08f;
		break;
	}
}
/*速度菜单函数*/
void VelocityMenu(int date)
{
	option_value = date;
	switch (option_value)
	{
	case 4://低速
		speedlevel = 1;
		break;
	case 5://中速
		speedlevel = 3;
		break;
	case 6://快速
		speedlevel = 5;
		break;
	}
}
/*显示菜单函数*/
void DisplayMenu(int date)
{
	option_value = date;
	switch (option_value)
	{
	case 7://填充
		LINE_or_FILL = 1;
		break;
	case 8://线框
		LINE_or_FILL = 0;
		break;
	}
}
/*主菜单函数*/
void MianMenu(int data)
{
	option_value = data;
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	/*初始化，创建窗口*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowPosition(400, 150);
	glutInitWindowSize(800,800);
	glutCreateWindow("高斌_大作业1");

	/*创建菜单*/
	/*变换一级菜单及子菜单*/
	int gaobin_TransformMenu = glutCreateMenu(TransformMenu);
	glutAddMenuEntry("Translation_Animation", 1);
	glutAddMenuEntry("Rotatation_Animation", 2);
	glutAddMenuEntry("Proportion_Animation", 3);
	/*速度一级菜单及子菜单*/
	int gaobin_VelocityMenu = glutCreateMenu(VelocityMenu);
	glutAddMenuEntry("Low_Speed", 4);
	glutAddMenuEntry("Medium_Speed", 5);
	glutAddMenuEntry("Fast_Speed", 6);
	/*显示一级菜单及子菜单*/
	int gaobin_DisplayMenu = glutCreateMenu(DisplayMenu);
	glutAddMenuEntry("Padding", 7);
	glutAddMenuEntry("Wireframe", 8);
	/*主菜单*/
	int gaobin_MainMenu = glutCreateMenu(MianMenu);
	glutAddSubMenu("TransformMenu", gaobin_TransformMenu);
	glutAddSubMenu("VelocityMenu", gaobin_VelocityMenu);
	glutAddSubMenu("DisplayMenu", gaobin_DisplayMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);//右键弹出菜单
	glutDisplayFunc(&gaobin_Triangle);
	glutMainLoop();     //消息循环（处理操作系统等的消息，例如键盘、鼠标事件等）
	return 0;
}