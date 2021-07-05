/*
opengl计算机图形学编程
高斌_大作业1
2021_7_2
*/
#include<Windows.h>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<gl/GL.h>
#include<gl/glut.h>
#include<gl/freeglut.h>
#include<cmath>
#define PI 3.1415926

/*灯颜色材质*/
GLfloat lightPos1[] = { 0.28f,0.23f,0.3f,1.0f };     /*第一个灯*/
GLfloat lightDirection1[] = { 0.0,-1.0,-1.0 };

GLfloat lightPos2[] = { 0.0f,0.5f,0.30f,1.0f };     /*第二个灯*/
GLfloat lightDirection2[] = { 1.0,-1.0,-1.0 };

GLfloat lightPos3[] = { -0.5f,-0.0f,0.1f,1.0f };    /*第三个灯*/
GLfloat lightDirection3[] = { 1.0,0.0,0.0 };

GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat specrof[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat ambientLight_whole[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat ambientLight[] = { 0.2f,0.2f,0.2f,1.0f };


/*旋转全局变量*/
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;

/*定义一个读取三维obj文件的类*/
class ObjLoader
{
public:
	struct vertex
	{
		float x;
		float y;
		float z;
	};
	ObjLoader(std::string filename);//读取函数
	void Draw();//绘制函数
private:
	std::vector<std::vector<GLfloat>> v;//存放顶点(x,y,z)坐标
	std::vector<std::vector<GLint>> f;//存放面的三个顶点索引
};
ObjLoader::ObjLoader(std::string filename)
{
	std::ifstream file(filename);
	std::string line;
	while (getline(file, line))
	{
		if (line.substr(0, 1) == "v")
		{
			std::vector<GLfloat> Point;
			GLfloat x, y, z;
			std::istringstream s(line.substr(2));
			s >> x;
			s >> y; 
			s >> z;
			Point.push_back(x);
			Point.push_back(y);
			Point.push_back(z);
			v.push_back(Point);
		}
		else if (line.substr(0, 1) == "f")
		{
			std::vector<GLint> vIndexSets;
			GLint u, v, w;
			std::istringstream vtns(line.substr(2));
			vtns >> u; vtns >> v; vtns >> w;
			vIndexSets.push_back(u - 1);
			vIndexSets.push_back(v - 1);
			vIndexSets.push_back(w - 1);
			f.push_back(vIndexSets);
		}
	}
	file.close();
}
void ObjLoader::Draw()
{
	glBegin(GL_TRIANGLES);//开始绘制
	for (int i = 0; i < f.size(); i++)
	{
		vertex a, b, c;	//三个顶点
		if ((f[i]).size() != 3) 
		{
			std::cout << "ERRER::THE SIZE OF f IS NOT 3!" << std::endl;
		}
		else {
			GLint firstVertexIndex = (f[i])[0];//取出顶点索引
			GLint secondVertexIndex = (f[i])[1];
			GLint thirdVertexIndex = (f[i])[2];

			a.x = (v[firstVertexIndex])[0];//第一个顶点
			a.y = (v[firstVertexIndex])[1];
			a.z = (v[firstVertexIndex])[2];

			b.x = (v[secondVertexIndex])[0]; //第二个顶点
			b.y = (v[secondVertexIndex])[1];
			b.z = (v[secondVertexIndex])[2];

			c.x = (v[thirdVertexIndex])[0]; //第三个顶点
			c.y = (v[thirdVertexIndex])[1];
			c.z = (v[thirdVertexIndex])[2];
			
			/*左下角孔颜色*/
			if ((a.x >= 0.03&&a.x <= 0.12&&a.y>= 0.03&&a.y<= 0.12)/*第一个顶点在孔内*/
				&&
				(b.x >= 0.03&&b.x <= 0.12&&b.y >= 0.03&&b.y<= 0.12)/*第二个顶点在孔内*/
				&&
				(c.x >= 0.03&&c.x <= 0.12&&c.y >= 0.03&&c.y <= 0.12))/*第三个顶点在孔内*/
			{
				glColor3f(1.0, 0.0, 0.0);
			}

			/*右下角孔颜色*/
			else if ((a.x >= 0.43&&a.x <= 0.51&&a.y >= 0.03&&a.y <= 0.12)/*第一个顶点在孔内*/
				&&
				(b.x >= 0.43&&b.x <= 0.51&&b.y >= 0.03&&b.y <= 0.12)/*第二个顶点在孔内*/
				&&
				(c.x >= 0.43&&c.x <= 0.51&&c.y >= 0.03&&c.y <= 0.12))/*第三个顶点在孔内*/
			{
				glColor3f(1.0, 0.0, 0.0);
			}

			/*左上角孔颜色*/
			else if ((a.x >= 0.065&&a.x <= 0.095&&a.y >= 0.205&&a.y <= 0.245)/*第一个顶点在孔内*/
				&&
				(b.x >= 0.065&&b.x <= 0.095&&b.y >= 0.205&&b.y <= 0.245)/*第二个顶点在孔内*/
				&&
				(c.x >= 0.065&&c.x <= 0.095&&c.y >= 0.205&&c.y <= 0.245))/*第三个顶点在孔内*/
			{
				glColor3f(1.0, 0.0, 0.0);
			}

			/*右上角孔颜色*/
			else if ((a.x >= 0.455&&a.x <= 0.485&&a.y >= 0.205&&a.y <= 0.245)/*第一个顶点在孔内*/
				&&
				(b.x >= 0.455&&b.x <= 0.485&&b.y >= 0.205&&b.y <= 0.245)/*第二个顶点在孔内*/
				&&
				(c.x >= 0.455&&c.x <= 0.485&&c.y >= 0.205&&c.y <= 0.245))/*第三个顶点在孔内*/
			{
				glColor3f(1.0, 0.0, 0.0);
			}

			/*右上角孔颜色*/
			else if ((a.x >= 0.455&&a.x <= 0.495&&a.y >= 0.205&&a.y <= 0.245)/*第一个顶点在孔内*/
				&&
				(b.x >= 0.455&&b.x <= 0.495&&b.y >= 0.205&&b.y <= 0.245)/*第二个顶点在孔内*/
				&&
				(c.x >= 0.455&&c.x <= 0.495&&c.y >= 0.205&&c.y <= 0.245))/*第三个顶点在孔内*/
			{
				glColor3f(1.0, 0.0, 0.0);
			}

			/*中间圆槽颜色*/
			else if ((a.x >= 0.25&&a.x <= 0.30&&a.z >= 0.1&&a.z<= 0.3)/*第一个顶点在孔内*/
				&&
				(b.x >= 0.25&&b.x <= 0.30&&b.z >= 0.1 && b.z <= 0.3)/*第二个顶点在孔内*/
				&&
				(c.x >= 0.25&&c.x <= 0.30&&c.z >= 0.1 && c.z <= 0.3))/*第三个顶点在孔内*/
			{
				glColor3f(0.0, 0.0, 1.0);
			}
	        /*剩余颜色*/
			else glColor3f(0.0, 1.0, 0.0);
			glVertex3f(a.x*1.5, a.y*1.5, -a.z*1.5);//绘制三角面
			glVertex3f(b.x*1.5, b.y*1.5, -b.z*1.5);
			glVertex3f(c.x*1.5, c.y*1.5, -c.z*1.5);
		}
	}
	glEnd();
}
ObjLoader monkey = ObjLoader("openglOBJ.obj");

void gaobin_Object(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清除所有的像素, 清除屏幕颜色，即将屏幕的所有像素点都还原为 “底色 ”。
	/*背景*/
	glBegin(GL_POLYGON);              //多边形
		glColor3f(1.0f, 0.84f, 0.84f);
		glVertex3f(-1.0f, -1.0f, 0.6f); //左下
		glVertex3f(1.0f, -1.0f,0.6f);  //右下
		glColor3f(1.0f, 0.76f, 0.45f);   
		glVertex3f(1.0f, 1.0f,  0.6f);  //右上
		glVertex3f(-1.0f, 1.0f, 0.6f);  //左上
	glEnd();
	/*模型变换和视图变换*/
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();                    //保证每一次操作的对象只限定于物体这个矩阵
	    /*分别绕x,y,z旋转*/
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glRotatef(zRot, 0.0f, 0.0f, 1.0f);   
		/*绘制物体*/
		monkey.Draw();	
	glPopMatrix();                        //保证每一次操作的对象只限定于物体这个矩阵
	glutPostRedisplay();
	glutSwapBuffers();
}
/*普通按键*/
void KeyboardKeys(unsigned char key, int x, int y)
{
	if (key == 32)
		zRot -= 5.0f;
}
/*特殊按键*/
void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if (key == GLUT_KEY_LEFT)
		yRot += 5.0f;
	if (key == GLUT_KEY_RIGHT)
		yRot -= 5.0f;
	if (key == GLUT_KEY_F5)
		zRot += 5.0f;
	glutPostRedisplay();
	glutSwapBuffers();
}

void SetupRC(void)
{
	glEnable(GL_DEPTH_TEST);                                //当前像素前面是否有别的像素，如果别的像素挡道了它，那它就不会绘制
	/*环境光*/
	glEnable(GL_LIGHTING);                                   //开灯
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight_whole);   //全局环境光，提供轻微的环境光，以便可以看到物体；整个场景的环境光的RGBA的强度
	/*1号灯*/
	glLightfv(GL_LIGHT0, GL_DIFFUSE, ambientLight);     //光源中的散射光强度（光仅由漫反射和镜面反射组成）
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);        //光源中的镜面反射光强度
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);        //指定光源位置
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection1);  // 聚光灯主轴方向  spot direction
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF,180.0f);         //指定光源的最大散布角 （创建聚光灯，v表示参数是向量（数组））
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT,500.0f);      //指定聚焦光源指数
	glEnable(GL_LIGHT0);                                 //启动0号光源
	/*2号灯*/
	glLightfv(GL_LIGHT1, GL_DIFFUSE, ambientLight);     //光源中的散射光强度（光仅由漫反射和镜面反射组成）
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);        //光源中的镜面反射光强度
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);        //指定光源位置
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDirection2);  // 聚光灯主轴方向  spot direction
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0f);         //指定光源的最大散布角 （创建聚光灯，v表示参数是向量（数组））
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 500.0f);      //指定聚焦光源指数
	glEnable(GL_LIGHT1);                                 //启动1号光源
	/*3号灯*/
	glLightfv(GL_LIGHT2, GL_DIFFUSE, ambientLight);     //光源中的散射光强度（光仅由漫反射和镜面反射组成）
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);        //光源中的镜面反射光强度
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);        //指定光源位置
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightDirection3);  // 聚光灯主轴方向  spot direction
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 60.0f);         //指定光源的最大散布角 （创建聚光灯，v表示参数是向量（数组））
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 500.0f);      //指定聚焦光源指数
	glEnable(GL_LIGHT2);                                 //启动2号光源

	glEnable(GL_COLOR_MATERIAL);                            //使用颜色材质，颜色追踪。激活光照的情况下用glColor函数给物体上色
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);   //来决定对物体的正面还是反面，对环境光、镜面光还是漫射光进行颜色跟踪
	
    glMaterialfv(GL_FRONT, GL_SPECULAR, specrof);        //材质的镜面反射颜色
	glMateriali(GL_FRONT, GL_SHININESS, 128);            //镜面反射指数
	glDepthFunc(GL_LEQUAL);          
}
/*主函数*/
int main(int argc, char* argv[])
{
	/*初始化，创建窗口*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(400, 150);
	glutInitWindowSize(800, 800);
	glutCreateWindow("高斌_大作业2");
	/*键盘命令*/
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(KeyboardKeys);
	/*调用绘制*/
	SetupRC();
	glutDisplayFunc(&gaobin_Object);
	glutMainLoop();     //消息循环（处理操作系统等的消息，例如键盘、鼠标事件等）
	return 0;
}