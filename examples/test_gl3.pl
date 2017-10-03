:- use_module(library(opengl/plgl)).


% To provide the (re)display and (re)shape functions, one normally
% provides a C function. Trivially, this is replaced with the predicates
% glut_reshape_function/0 and glut_display_function.

glut_reshape_function(W,H) :-
	L is min(W,H),
	X is floor((W-L)/2),
	Y is floor((H-L)/2),
	% NegL is -L,
	%	format('setting viewport: (~d x ~d) + (~d,~d).\n',[L,L,X,Y]),
	gl_viewport(X,Y,L,L).
%	gl_matrix_mode(gl_GL_PROJECTION),
%  glu_perspective(40.0,1.0,1.0,10.0).
%	gl_load_identity,
%	gl_ortho(0,L,0,L,-1,1),
%	gl_scale(1,-1,1),
%	gl_translate(0,NegL,0).

init:-
	% initialise, create a window and put a sphere in it. Then duplicate window.
    glut_init,
    glut_init_display_mode( glut_GLUT_DOUBLE \/ glut_GLUT_RGB \/ glut_GLUT_DEPTH),
    glut_create_window('sphere'),
    glut_reshape_cb,
    glut_display_cb,
	 gfxinit.
	 %  glut_create_window('a second window'),
	 %  glut_display_cb,
	 %    gfxinit.

go :- glut_main_loop.

gfxinit:-
    glu_new_quadric(QuadricPtr),
    glu_quadric_draw_style(QuadricPtr,glu_GLU_FILL),
    gl_new_list(1,gl_GL_COMPILE),
    glu_sphere(QuadricPtr,1.0,40,40),
    gl_end_list,
    gl_lightfv(gl_GL_LIGHT0,gl_GL_DIFFUSE, [1, 0, 0, 1]),
    gl_lightfv(gl_GL_LIGHT0,gl_GL_POSITION,[1, 0, 0, 0]),
    gl_lightfv(gl_GL_LIGHT1,gl_GL_DIFFUSE, [0, 1, 0, 1]),
    gl_lightfv(gl_GL_LIGHT1,gl_GL_POSITION,[0, 1, 0, 0]),
    gl_lightfv(gl_GL_LIGHT2,gl_GL_DIFFUSE, [0, 0, 1, 1]),
	 gl_lightfv(gl_GL_LIGHT2,gl_GL_POSITION,[-1, -1, -1, 0]),
    gl_enable(gl_GL_LIGHTING),
    gl_enable(gl_GL_LIGHT0),
    gl_enable(gl_GL_LIGHT1),
    gl_enable(gl_GL_LIGHT2),
    gl_enable(gl_GL_DEPTH_TEST),
    gl_matrix_mode(gl_GL_PROJECTION),
    glu_perspective(40.0,1.0,1.0,10.0),
    gl_matrix_mode(gl_GL_MODELVIEW),
    glu_look_at(0.0,0.0,5.0,
		  0.0,0.0,0.0,
		  0.0,1.0,0.0),
    gl_translate(0.0,0.0,-1.0).

glut_display_function :- 
	 gl_clear(gl_GL_COLOR_BUFFER_BIT \/ gl_GL_DEPTH_BUFFER_BIT),
	 gl_call_list(1),
    glut_swap_buffers.


