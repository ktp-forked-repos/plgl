:- use_module(library(opengl/plgl)).

% To provide the (re)display and (re)shape functions, one normally
% provides a C function. Trivially, this is replaced with the predicates
% glut_reshape_function/0 and glut_display_function.

glut_reshape_function(W,H) :-
	L is min(W,H),
	X is floor((W-L)/2),
	Y is floor((H-L)/2).
%	gl_viewport(X,Y,L,L).

init:-
	% initialise, create a window and put a sphere in it. Then duplicate window.
    glut_init,
    glut_init_display_mode( glut_GLUT_DOUBLE \/ glut_GLUT_RGB),
    glut_create_window('flatland'),
    glut_reshape_cb,
    glut_display_cb.

go :- 
    glut_main_loop.

glut_display_function :- 
	 gl_clear(gl_GL_COLOR_BUFFER_BIT),
	 gl_begin(gl_GL_TRIANGLES),
	 gl_vertex2i(-1,-1),
	 gl_vertex2i(1,0),
	 gl_vertex2i(0,1),
	 gl_end,
    glut_swap_buffers.


