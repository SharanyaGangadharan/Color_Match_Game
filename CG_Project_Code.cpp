#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int f=1;
int i,j;
int i2,j2;
int flags=0;
char tmp_str[40];
int tiles[3][3]={{0,0,0},{0,0,0},{0,0,0}};
int grid[2][4]={{600,400,200,0},{0,200,400,600}};
GLfloat color[][3]={{1,1,1},{},{1,1,0},{},{1,0.5,0},{},{},{},{1,0,0},{},{},{},{},{},{},{},{0.5,0,0},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{0,1,1},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{0,0,1},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{0,0,0}};
int ran_num();
int pushUp();
int pushDown();
int pushRight();
int pushLeft();
void processSpecialkeys(int,int,int);
void NormalKey(GLubyte, GLint, GLint);

void print(char *string)
{
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
}

void print1(char *string)
{
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}

void display()
{
	int time=0,time1=0;
	glClear(GL_COLOR_BUFFER_BIT);
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			int p=tiles[i][j];
			glColor3fv(color[p]);
			glBegin(GL_POLYGON);
			glVertex2i(grid[1][j],grid[0][i]);
			glVertex2i(grid[1][j],grid[0][i+1]);
			glVertex2i(grid[1][j+1],grid[0][i+1]);
			glVertex2i(grid[1][j+1],grid[0][i]);
			glEnd();

			   glColor3f(0,0,0);
			   glBegin(GL_LINES);
			   	glVertex2i(200,0);
			   	glVertex2i(200,600);
			   glEnd();

			   glColor3f(0,0,0);
			   glBegin(GL_LINES);
			   	glVertex2i(400,0);
			   	glVertex2i(400,600);
			   glEnd();

			   glColor3f(0,0,0);
			   glBegin(GL_LINES);
			   	glVertex2i(0,200);
			   	glVertex2i(600,200);
			   glEnd();

        		   glColor3f(0,0,0);
			   glBegin(GL_LINES);
			   	glVertex2i(0,400);
			   	glVertex2i(600,400);
			   glEnd();

			   glColor3f(0,0,0);
			   glBegin(GL_LINE_LOOP);
				   glVertex2i(0,0);
				   glVertex2i(600,0);
				   glVertex2i(600,600);
				   glVertex2i(0,600);
			   glEnd();

			   for(i2=0;i2<3;i2++)
			   {
				for(j2=0;j2<3;j2++)
				{
					if(tiles[i2][j2]==128)//player wins when black tile is reached
					{
						glFlush();
						for(time=0;time<=100000000;time++) {}
						glClear(GL_COLOR_BUFFER_BIT);
						glClearColor(0.0,0.0,0.0,1.0);
						glColor3f(1,0,0);
						glRasterPos2i(215,325);
						sprintf(tmp_str,"YOU WIN!!!");
						print(tmp_str);
						glFlush();
						for(time1=0; time1<=100000000;time1++) {}
						exit(0);
					}
				}
			   }
			for(i2=0;i2<3;i2++)
			{
				for(j2=0;j2<3;j2++)
				{
					if((tiles[i2][j2]!=tiles[i2][j2+1] && tiles[i2][j2]!=0 && tiles[i2][j2+1]!=0) && (tiles[i2][j2]!=tiles[i2+1][j2] && tiles[i2][j2]!=0 && tiles[i2+1][j2]!=0))//to check if there are no more same colored adjacent tiles left
					{
						flags=1;
					}
					else
					{
						flags=0;
					}
				}
			}
			if(flags==1)//Game Over condition
			{
				glClear(GL_COLOR_BUFFER_BIT);
				glClearColor(0.0,0.0,0.0,1.0);
				glColor3f(1,0,0);
				glRasterPos2i(215,325);
				sprintf(tmp_str,"GAME OVER!!!");
				print(tmp_str);
				for(time1=0;time1<=100000000;time++) {}
				exit(0);
			}
			else if(flags==0)
			{
				continue;
			}
		}
	}
	glFlush();
}

void myReshape(int w,int h)
{
	glClearColor(1.0,1.0,1.0,1.0);
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPointSize(5.0);
	gluOrtho2D(0,600,0,600);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void processSpecialKeys(int key, int x, int y)
{
		int i1,j1;
		if(key==GLUT_KEY_UP)
		{	
			pushUp();
			display();
		}
		else if(key==GLUT_KEY_DOWN)
		{	
			pushDown();
			display();						
		}	
		else if(key==GLUT_KEY_LEFT)
		{
			pushLeft();
			display();
						
		}
		else if(key==GLUT_KEY_RIGHT)
		{
			pushRight();
		  	display();		
		}	
}

int ran_num()
{
	int i2,j2;
	i2=(rand()%3),j2=(rand()%3);
	if(tiles[i2][j2]==0)
	{
		tiles[i2][j2]=2;
		return 0;
	}
	ran_num();
}

int pushLeft()
{
    int i, j, k;
    for(i = 0; i < 3; i++)
    {		
        for(j = 1; j < 3; j++)
        {
            if(tiles[i][j]!=0) //tile is not empty
            {
                 int flag = 1; //flag to prevent merging more than one level at a time
                //Starting on column k, push tile as far to the left as possible
                for(k = j; k > 0; k--)
                {
                    if( tiles[i][k-1] == 0) //adjacent tile is empty
                    {
                         tiles[i][k-1] =  tiles[i][k];
                         tiles[i][k] = 0;
                    }
                    else if( tiles[i][k-1] ==  tiles[i][k] && flag) //adjacent equals
                    {
                         tiles[i][k-1]+=tiles[i][k];
                         tiles[i][k] = 0;
                         flag = 0;
                    }
                    else //Can't push or merge
                    {
                        flag = 1;
                        break;
                    }
                }
            }
        } 
    }
   ran_num();
    return 0;
}

int pushRight()
{
    int i, j, k;
    for(i = 0; i < 3; i++)
    {
        for(j = 1; j >= 0; j--) 
        {
            if( tiles[i][j] != 0)
            {
                int flag = 1;
                for(k = j; k <2; k++)
                {
                    if( tiles[i][k+1] == 0) 
                    {
                         tiles[i][k+1] =  tiles[i][k];
                         tiles[i][k] = 0;
                    }
                    else if( tiles[i][k+1] ==  tiles[i][k] && flag)
                    {
                         tiles[i][k+1]+=tiles[i][k];
                         tiles[i][k] = 0;
                         flag = 0;
                    }
                    else 
                    {
                        flag = 1;
                        break;
                    }
                }
            }
        } 
    }
	ran_num();
	 return 0;
}

int pushUp()
{
    int i, j, k;
    for(i = 0; i < 3;i++)
    {
        for(j = 1; j < 3; j++)
        {
            if( tiles[j][i] != 0) 
            {
                int flag = 1;
                for(k = j; k >0; k--)
                {
                    if( tiles[k-1][i] ==0) 
                    {
                         tiles[k-1][i] =  tiles[k][i];
                         tiles[k][i] = 0;
                    }
                    else if( tiles[k-1][i] ==  tiles[k][i] && flag) 
                    {
                         tiles[k-1][i]+=tiles[k][i];
                         tiles[k][i] =0;
                         flag = 0;
                    }
                    else 
                    {
                        flag = 1;
                        break;
                    }
                }
            }
        } 
    }
	ran_num();
	 return 0;
}

int pushDown()
{
    int i, j, k;
    for(i = 0; i <3; i++) 
    {
        for(j = 1; j >= 0; j--) 
        {
            if( tiles[j][i] != 0) 
            {
                int flag = 1; 
                for(k = j; k < 2; k++)
                {
                    if( tiles[k+1][i] == 0) 
                    {
                         tiles[k+1][i] =  tiles[k][i];
                         tiles[k][i] = 0;
                    }
                    else if( tiles[k+1][i] == tiles[k][i] && flag)
                    {
                         tiles[k+1][i]+=tiles[k][i];
                         tiles[k][i] = 0;
                         flag = 0;
                    }
                    else 
                    {
                        flag = 1;
                        break;
                    }
                }
            }
        } 
    }
	ran_num();
	 return 0;
}

void Intro()
{	
	char tmp_str[40];	
	glColor3f(1, 1, 1);
	glRasterPos2i(125,450);
	sprintf(tmp_str,"COMPUTER GRAPHICS PROJECT");
	print(tmp_str);
	glColor3f(1, 1, 1);
	glRasterPos2i(200, 400);
	sprintf(tmp_str, "COLOUR MATCH");
	print(tmp_str);
	glColor3f(1, 0, 0);
	glRasterPos2i(225,275);
	sprintf(tmp_str,"Press P to PLAY");
	print1(tmp_str);
	glColor3f(0, 0, 1);
	glRasterPos2i(225,225);
	sprintf(tmp_str,"Press H for Help");
	print1(tmp_str);
	glColor3f(0, 0, 1);
	glRasterPos2i(225,200);
	sprintf(tmp_str,"Press Q to Quit");
	print1(tmp_str);
	glColor3f(1, 1, 1);
	glRasterPos2i(175,80);
	sprintf(tmp_str,"Sharanya Gangadharan (1CR12CS091)");
	print1(tmp_str);
	glColor3f(1, 1, 1);
	glRasterPos2i(175,40);
	sprintf(tmp_str,"Shruthi Suresh (1CR12CS103)");
	print1(tmp_str);
	glFlush();
}

void dis()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	if(f==0)
		display();
	else if(f==1)
		Intro();
}

void NormalKey(GLubyte key, GLint x, GLint y) 
{
	int time=0;
	if(f==1)
	{		
		f=0;
	}
	if(key=='p')
	{
		dis();
	}
	if(key=='h')
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0,0.0,0.0,1.0);
		glColor3f(0,1,1);
		glRasterPos2i(260,500);
		sprintf(tmp_str,"RULES");
		print(tmp_str);
		glColor3f(0,1,0);
		glRasterPos2i(80,400);
		sprintf(tmp_str,"1: Press UP arrow key to move the tiles upwards");
		print1(tmp_str);
		glColor3f(0,1,0);
		glRasterPos2i(80,325);
		sprintf(tmp_str,"2: Press DOWN arrow key to move the tiles downwards");
		print1(tmp_str);
		glColor3f(0,1,0);
		glRasterPos2i(80,250);
		sprintf(tmp_str,"3: Press LEFT arrow key to move the tiles to the left");
		print1(tmp_str);
		glColor3f(0,1,0);
		glRasterPos2i(80,175);
		sprintf(tmp_str,"4: Press RIGHT arrow key to move the tiles to the right");
		print1(tmp_str);
		glColor3f(1,0,0);
		glRasterPos2i(225,100);
		sprintf(tmp_str,"Press P to PLAY");
		print1(tmp_str);
		glFlush();
	}
	if(key=='q')
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0,0.0,0.0,1.0);
		glColor3f(1,0,0);
		glRasterPos2i(215,325);
		sprintf(tmp_str,"GAME OVER!!!");
		print(tmp_str);
		glFlush();
		for (time =0; time<=100000000;time++) {}
		exit(0);
	}
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
   glutInitWindowSize(600,600);
   glutInitWindowPosition (0,0);
   glutCreateWindow("Colour Match");
   glutReshapeFunc(myReshape);
   glutDisplayFunc(dis);
   glutSpecialFunc(processSpecialKeys);
   glutKeyboardFunc(NormalKey);
   glutMainLoop();
   return 0;
}
