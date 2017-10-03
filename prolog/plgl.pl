:- module(plgl,
		[	glut_init/0
		,	glut_init_display_mode/1
		,	glut_create_window/1
		,	glut_display_cb/0
		,	glut_reshape_cb/0
		,	glut_main_loop/0
		,	glut_swap_buffers/0

		,	glu_perspective/4
		,	glu_look_at/9
		,	glu_sphere/4
		,	glu_new_quadric/1
		,	glu_quadric_draw_style/2

		,	gl_begin/1
		,	gl_end/0
		,	gl_flush/0
		,	gl_clear/1
		,	gl_enable/1
		,	gl_ortho/6
		,	gl_viewport/4
		,	gl_matrix_mode/1
		,	gl_load_identity/0
		,	gl_translate/3
		,	gl_scale/3
		,	gl_new_list/2
		,	gl_end_list/0
		,	gl_vertex2i/2
		,	gl_color3f/3
		,	gl_lightfv/3
		,	gl_call_list/1
		]).
		

:- use_module(gl_defs).
:- use_module(glu_defs).
:- use_module(glut_defs).

:- load_foreign_library(foreign(plgl)).

% ----------------------------- GLUT ----------------------------------

glut_init :- c_glutInit.

glut_init_display_mode(Opts) :- glut_opts(Opts,OVal), c_glutInitDisplayMode(OVal).
glut_create_window(Title) :- c_glutCreateWindow(Title).
glut_swap_buffers :- c_glutSwapBuffers.
glut_main_loop    :- c_glutMainLoop.


glut_display_cb :- 
	write_ln('glutDisplayFunc will call user:glut_display_function/0'),
	c_glutDisplayFunc.

glut_reshape_cb :- 
	write_ln('glutReshapeFunc will call user:glut_reshape_function/0'),
	c_glutReshapeFunc.



% ----------------------------- GLU ----------------------------------

glu_sphere(PL_GluQuadricPtr,Radius,Slices,Stacks):-
	integer(Stacks),
	integer(Slices),
	float(Radius),
	c_gluSphere(PL_GluQuadricPtr,Radius,Slices,Stacks).

glu_new_quadric(PL_GluQuadricPtr):-
    c_gluNewQuadric(PL_GluQuadricPtr).

glu_quadric_draw_style(PL_GluQuadricPtr,Opts):-
	glu_opts(Opts,Val), c_gluQuadricDrawStyle(PL_GluQuadricPtr,Val).

glu_perspective(FovY,Aspect,ZNear,ZFar) :- 
	c_gluPerspective(FovY,Aspect,ZNear,ZFar).

glu_look_at(EyeX,EyeY,EyeZ, CX,CY,CZ, UpX,UpY,Upz):-
	c_gluLookAt(EyeX,EyeY,EyeZ, CX,CY,CZ, UpX,UpY,Upz).


% ----------------------------- GL ----------------------------------

gl_flush             :- c_glFlush.
gl_load_identity     :- c_glLoadIdentity.
gl_clear(Opts)       :- gl_opts(Opts,Val), c_glClear(Val).
gl_begin(Mode)       :- gl_opts(Mode,Val), c_glBegin(Val).
gl_end               :- c_glEnd.
gl_enable(Thing)     :- gl_opts(Thing,Val), c_glEnable(Val).
gl_matrix_mode(Mode) :- gl_opts(Mode,Val), c_glMatrixMode(Val).
gl_scale(KX,KY,KZ)   :- c_glScalef(KX,KY,KZ).
gl_translate(X,Y,Z)  :- c_glTranslatef(X,Y,Z).
gl_vertex2i(X,Y)     :- c_glVertex2i(X,Y).
gl_color3f(R,G,B)    :- c_glColor3f(R,G,B).
gl_call_list(Index)  :-	c_glCallList(Index).
gl_end_list          :- c_glEndList.

gl_ortho(Left,Right,Bottom,Top,Near,Far):- c_glOrtho(Left,Right,Bottom,Top,Near,Far).
gl_viewport(X,Y,Width,Height) :- c_glViewport(X,Y,Width,Height).
gl_new_list(DisplayListIndex,Opts):-
	integer(DisplayListIndex),
	gl_opts(Opts,Val), c_glNewList(DisplayListIndex,Val).

gl_lightfv(GL_Light,Params,[A,B,C,D]):-
	gl_opts(GL_Light,Light),
	gl_opts(Params,ParamVal),
	c_glLightfv(Light,ParamVal,A,B,C,D).
