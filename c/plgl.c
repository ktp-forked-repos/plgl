/* This file contains C functions to be called by prolog OpenGL predicates */

/* Todo
 *
 * better interface to options
 *	more API bindings:
 *		glutInitWindowSize / Position
 *		glVertex3f
 *		glVertex2f
 */

#ifdef USE_MACOS_GL
#	include <OpenGL/gl.h>
#	include <OpenGL/glu.h>
#	include <GLUT/glut.h>
#else
#	include <GL/gl.h>
#	include <GL/glu.h>
#	include <GL/glut.h>
#endif
#include <SWI-Prolog.h>
#include <stdio.h>


void c_glut_display(void);
void c_glut_reshape(int,int);
foreign_t c_glutDisplayFunc(void);
foreign_t c_glutReshapeFunc(void);
foreign_t c_glViewport(term_t X, term_t Y, term_t W, term_t H);
foreign_t c_glCallList(term_t Index);
foreign_t c_glClear(term_t Apply_options);
foreign_t c_glEnable(term_t Option);
foreign_t c_glLightfv(term_t Light,term_t ParamName,term_t A,term_t B,term_t C,term_t D);
foreign_t c_glMatrixMode(term_t Mode);
foreign_t c_glNewList(term_t DisplayListIndex,term_t OptionList);
foreign_t c_glTranslatef(term_t X,term_t Y,term_t Z);
foreign_t c_gluLookAt(term_t EyeX,term_t EyeY,term_t EyeZ,
		      term_t CenterX,term_t CenterY,term_t CenterZ,
		      term_t UpX,term_t UpY,term_t Upz);
foreign_t c_gluPerspective(term_t FovY,term_t Aspect,term_t zNear,term_t zFar);
foreign_t c_gluNewQuadric(term_t PL_gluQuadricPtr);
foreign_t c_gluQuadricDrawStyle(term_t gluQuadricPtr,term_t OptionList);
foreign_t c_gluSphere(term_t GLUquadricPtr,term_t Radius,term_t Slices,term_t Stacks);
foreign_t c_glutCreateWindow(term_t String);
foreign_t c_glutInit(void);
foreign_t c_glutInitDisplayMode(term_t AppliedList);
foreign_t c_glutSwapBuffers(void);
foreign_t c_glutMainLoop(void);
foreign_t c_glEndList(void);
foreign_t c_glLoadIdentity(void);
foreign_t c_glOrtho(term_t PL_Left,term_t PL_Right,term_t PL_Bottom,term_t PL_Top,term_t PL_Near,term_t PL_Far);
foreign_t c_glScalef(term_t XScale, term_t YScale, term_t ZScale);
foreign_t c_glBegin(term_t Mode);
foreign_t c_glEnd(void);
foreign_t c_glColor3f(term_t PL_Red, term_t PL_Green, term_t PL_Blue);
foreign_t c_glVertex2i(term_t PL_X, term_t PL_Y);
foreign_t c_glFlush(void);
foreign_t dl(void);

install_t install()
{
  PL_register_foreign("c_glCallList",1,c_glCallList,PL_FA_NOTRACE);
  PL_register_foreign("c_glClear",1,c_glClear,PL_FA_NOTRACE);
    PL_register_foreign("c_glEnable",1,c_glEnable,PL_FA_NOTRACE);
    PL_register_foreign("c_glLightfv",6,c_glLightfv,PL_FA_NOTRACE);
    PL_register_foreign("c_glMatrixMode",1,c_glMatrixMode,PL_FA_NOTRACE);
    PL_register_foreign("c_glNewList",2,c_glNewList,PL_FA_NOTRACE);
    PL_register_foreign("c_glTranslatef",3,c_glTranslatef,PL_FA_NOTRACE);
    PL_register_foreign("c_gluLookAt",9,c_gluLookAt,PL_FA_NOTRACE);
    PL_register_foreign("c_gluPerspective",4,c_gluPerspective,PL_FA_NOTRACE);
    PL_register_foreign("c_gluNewQuadric",1,c_gluNewQuadric,PL_FA_NOTRACE);
    PL_register_foreign("c_gluQuadricDrawStyle",2,c_gluQuadricDrawStyle,PL_FA_NOTRACE);
    PL_register_foreign("c_gluSphere",4,c_gluSphere,PL_FA_NOTRACE);
    PL_register_foreign("c_glutCreateWindow",1,c_glutCreateWindow,PL_FA_NOTRACE);
    PL_register_foreign("c_glutDisplayFunc",0,c_glutDisplayFunc,PL_FA_NOTRACE);
    PL_register_foreign("c_glutReshapeFunc",0,c_glutReshapeFunc,PL_FA_NOTRACE);
    PL_register_foreign("c_glutInit",0,c_glutInit,PL_FA_NOTRACE);
    PL_register_foreign("c_glutInitDisplayMode",1,c_glutInitDisplayMode,PL_FA_NOTRACE);
    PL_register_foreign("c_glutSwapBuffers",0,c_glutSwapBuffers,PL_FA_NOTRACE);
    PL_register_foreign("c_glutMainLoop",0,c_glutMainLoop,PL_FA_NOTRACE);
    PL_register_foreign("c_glEndList",0,c_glEndList,PL_FA_NOTRACE);
    PL_register_foreign("c_glViewport",4,c_glViewport,PL_FA_NOTRACE);
    PL_register_foreign("c_glLoadIdentity",0,c_glLoadIdentity,PL_FA_NOTRACE);
    PL_register_foreign("c_glOrtho",6,c_glOrtho,PL_FA_NOTRACE);
    PL_register_foreign("c_glScalef",3,c_glScalef,PL_FA_NOTRACE);
    PL_register_foreign("c_glBegin",1,c_glBegin,PL_FA_NOTRACE);
    PL_register_foreign("c_glEnd",0,c_glEnd,PL_FA_NOTRACE);
    PL_register_foreign("c_glColor3f",3,c_glColor3f,PL_FA_NOTRACE);
    PL_register_foreign("c_glVertex2i",2,c_glVertex2i,PL_FA_NOTRACE);
    PL_register_foreign("c_glFlush",0,c_glFlush,PL_FA_NOTRACE);
    PL_register_foreign("dl",0,dl,PL_FA_NOTRACE);
}

foreign_t dl(void)
{
  GLUquadricObj *qobj;
  qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj, GLU_FILL);
  glNewList(1, GL_COMPILE);  /* create sphere display list */
  gluSphere(qobj, /* radius */ 1.0, /* slices */ 20,
  /* stacks */ 20);
  //glEndList();
  PL_succeed;
}

/* OpenGL / libGL calls */

foreign_t c_glFlush(void) { glFlush(); PL_succeed; }

foreign_t c_glVertex2i(term_t PL_X, term_t PL_Y)
{
  GLint x, y;
  
  return PL_get_integer(PL_X,&x)
	  &&	PL_get_integer(PL_Y,&y)
	  && (glVertex2i(x,y), TRUE);
}

foreign_t c_glColor3f(term_t PL_Red, term_t PL_Green, term_t PL_Blue)
{
  GLdouble GLr, GLg, GLb;

  return PL_get_float(PL_Red,&GLr)
  		&&	PL_get_float(PL_Green,&GLg)
  		&&	PL_get_float(PL_Blue,&GLb)
	  	&& (glColor3f((float)GLr,(float)GLg,(float)GLb), TRUE);
}

foreign_t c_glBegin(term_t PL_Mode)
{
  int i_mode;
  
  return PL_get_integer(PL_Mode,&i_mode)
	  &&	(glBegin((GLenum)i_mode), TRUE);
}

foreign_t c_glEnd(void)
{
  glEnd();
  PL_succeed;
}

foreign_t c_glScalef(term_t XScale, term_t YScale, term_t ZScale)
{
  double x,y,z;

  return	PL_get_float(XScale,&x)
	  &&	PL_get_float(YScale,&y)
	  &&	PL_get_float(ZScale,&z)
     &&	(glScalef((float)x,(float)y,(float)z), TRUE);
}

foreign_t c_glOrtho(term_t PL_Left,term_t PL_Right,term_t PL_Bottom,term_t PL_Top,term_t PL_Near,term_t PL_Far)
{
  GLdouble left,right,bottom,top,near,far;

  return	PL_get_float(PL_Left,&left)
		&&	PL_get_float(PL_Right,&right)
		&&	PL_get_float(PL_Bottom,&bottom)
		&&	PL_get_float(PL_Top,&top)
		&&	PL_get_float(PL_Near,&near)
		&&	PL_get_float(PL_Far,&far)
  		&& (glOrtho(left,right,bottom,top,near,far), TRUE);
}

foreign_t c_glLoadIdentity(void) { glLoadIdentity(); PL_succeed; } 

foreign_t c_glViewport(term_t PL_X, term_t PL_Y, term_t PL_W, term_t PL_H)
{
  GLint x,y;
  GLsizei w,h;

  return PL_get_integer(PL_X,&x)
		&&	PL_get_integer(PL_Y,&y)
		&&	PL_get_integer(PL_W,&w)
		&&	PL_get_integer(PL_H,&h)
  		&& (glViewport(x,y,w,h), TRUE);
}


foreign_t c_glEndList(void) { glEndList(); PL_succeed; }

foreign_t c_glCallList(term_t PL_index)
{
  int display_list_id;
  return PL_get_integer(PL_index,&display_list_id)
      && (glCallList((GLuint)display_list_id), TRUE);
}

foreign_t c_glClear(term_t options)
{
  int mask;
  
  return PL_get_integer(options,&mask)
  	 &&	(glClear((GLbitfield)mask), TRUE);
}

foreign_t c_glEnable(term_t option)
{
  int capability;
  
  return PL_get_integer(option,&capability)
     && 	(glEnable((GLenum)capability), TRUE);
}

foreign_t c_glLightfv(term_t PL_Light,term_t PL_ParamName,term_t PL_A,term_t PL_B,term_t PL_C,term_t PL_D)
{
  int    light, paramname;
  double t[4];

  if (	PL_get_float(PL_A,&t[0])
		&&	PL_get_float(PL_B,&t[1])
		&&	PL_get_float(PL_C,&t[2])
		&&	PL_get_float(PL_D,&t[3])
		&&	PL_get_integer(PL_Light,&light)
		&&	PL_get_integer(PL_ParamName,&paramname)) 
  {
	  GLfloat p[4];
	  int i;

	  for (i=0; i<4; i++) p[i]=(GLfloat)t[i];
	  glLightfv((GLenum)light,(GLenum)paramname,p);
	  return TRUE;
	} else return FALSE;
}

foreign_t c_glMatrixMode(term_t PL_Mode)
{
  int mode;

  return PL_get_integer(PL_Mode,&mode)
     &&  (glMatrixMode((GLenum)mode),TRUE);
}

foreign_t c_glNewList(term_t PL_DisplayListIndex,term_t PL_OptionList)
{

  int list;
  int mode;

  return PL_get_integer(PL_DisplayListIndex,&list)
    	&&	PL_get_integer(PL_OptionList,&mode)
    	&&	(glNewList((GLuint)list,(GLenum)mode),TRUE);
}

foreign_t c_glTranslatef(term_t PL_X,term_t PL_Y,term_t PL_Z)
{
  double X,Y,Z;

  return PL_get_float(PL_X,&X)
	  &&	PL_get_float(PL_Y,&Y)
	  &&	PL_get_float(PL_Z,&Z)
	  &&	(glTranslatef((GLfloat)X,(GLfloat)Y,(GLfloat)Z), TRUE);
}

/* GLU Interaction */

foreign_t c_gluLookAt(term_t PL_EyeX,term_t PL_EyeY,term_t PL_EyeZ,
		      term_t PL_CenterX,term_t PL_CenterY,term_t PL_CenterZ,
		      term_t PL_UpX,term_t PL_UpY,term_t PL_UpZ)
{
  GLdouble iX,iY,iZ,cX,cY,cZ,uX,uY,uZ;

  return	PL_get_float(PL_EyeX,&iX)
		&&	PL_get_float(PL_EyeY,&iY)
		&&	PL_get_float(PL_EyeZ,&iZ)
		&&	PL_get_float(PL_CenterX,&cX)
		&&	PL_get_float(PL_CenterY,&cY)
		&&	PL_get_float(PL_CenterZ,&cZ)
		&&	PL_get_float(PL_UpX,&uX)
		&&	PL_get_float(PL_UpY,&uY)
		&&	PL_get_float(PL_UpZ,&uZ)
		&& ( gluLookAt((GLdouble)iX,(GLdouble)iY,(GLdouble)iZ,
			 (GLdouble)cX,(GLdouble)cY,(GLdouble)cZ,
			 (GLdouble)uX,(GLdouble)uY,(GLdouble)uZ),
			TRUE);
}

foreign_t c_gluPerspective(term_t PL_FovY,term_t PL_Aspect,term_t PL_zNear,term_t PL_zFar)
{
	GLdouble fovy,aspect,zNear,zFar;
	return	PL_get_float(PL_FovY,&fovy)
			&&	PL_get_float(PL_Aspect,&aspect)
			&&	PL_get_float(PL_zNear,&zNear)
			&&	PL_get_float(PL_zFar,&zFar)
			&&	(	gluPerspective((GLdouble)fovy,(GLdouble)aspect,(GLdouble)zNear,(GLdouble)zFar), 
					TRUE);
}

foreign_t c_gluNewQuadric(term_t PL_gluQuadricPtr)
{
	GLUquadricObj *qptr = gluNewQuadric();
	if (qptr) {
		printf("gluNewQuadric(): addess of object is %p.\n",qptr);
		return PL_unify_pointer(PL_gluQuadricPtr,qptr);
	} else return FALSE;
}

foreign_t c_gluQuadricDrawStyle(term_t PL_gluQuadricPtr,term_t PL_OptionList)
{
  // GLUquadricObj
  void *quadric;
  int draw;
  return PL_get_pointer(PL_gluQuadricPtr,&quadric)
		&&	PL_get_integer(PL_OptionList,&draw)
		&&	(gluQuadricDrawStyle(quadric,(GLenum)draw), TRUE);
}

foreign_t c_gluSphere(term_t PL_gluQuadricPtr,term_t PL_Radius,term_t PL_Slices,term_t PL_Stacks)
{
  void *gluQuadricPtr;
  GLdouble radius;
  GLint slices, stacks;

  return PL_get_pointer(PL_gluQuadricPtr,&gluQuadricPtr)
		&&	PL_get_float(PL_Radius,&radius)
		&&	PL_get_integer(PL_Slices,&slices)
		&&	PL_get_integer(PL_Stacks,&stacks)
		&&	(gluSphere(gluQuadricPtr,(GLdouble)radius,(GLint)slices,(GLint)stacks), TRUE);
}

/* GLUT Interaction */

foreign_t c_glutCreateWindow(term_t PL_String)
{
  char *string;
  return PL_get_atom_chars(PL_String,&string)
  		&&	(glutCreateWindow(string), TRUE);
}

void c_glut_reshape(int width, int height)
{
  static predicate_t reshape_pred;
  term_t params = PL_new_term_refs(2);

  if (!reshape_pred) 
	  reshape_pred = PL_predicate("glut_reshape_function",2,"user");

  if (!(	PL_put_integer(params,width)
    	&&	PL_put_integer(params+1,height)
  		&&	PL_call_predicate(NULL,PL_Q_NORMAL,reshape_pred,params)))
  {
	  printf("plgl: reshape callback failed.\n");
	}
}


void c_glut_display(void) 
{
  static predicate_t display0;
  static term_t params;

  if (!params) params= PL_new_term_refs(1);
  if (!display0) display0 = PL_predicate("glut_display_function",0,"user");
  if (!PL_call_predicate(NULL,PL_Q_NORMAL,display0,params)) {
	  printf("plgl: display callback failed.\n");
	}
}

foreign_t c_glutReshapeFunc(void) { glutReshapeFunc(c_glut_reshape); PL_succeed; }
foreign_t c_glutDisplayFunc(void) { glutDisplayFunc(c_glut_display); PL_succeed; }

foreign_t c_glutInit(void)
{
  int argc=2;
  char *argv[3];

  argv[0]="swipl";
  argv[1]="-gldebug";
  argv[2]=NULL;
  glutInit(&argc,argv);
  PL_succeed;
}

foreign_t c_glutInitDisplayMode(term_t PL_AppliedList)
{
  int mode;

  return PL_get_integer(PL_AppliedList,&mode)
     &&  (glutInitDisplayMode((unsigned int)mode),TRUE);
}

foreign_t c_glutSwapBuffers(void)
{
  glutSwapBuffers();
  PL_succeed;
}

foreign_t c_glutMainLoop(void)
{
  printf("plgl: calling glutMainLoop(), WILL NEVER RETURN! (goodbye....)\n");
  glutMainLoop();
  return TRUE;
}
