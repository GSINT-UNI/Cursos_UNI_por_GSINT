#! /usr/bin/env python
'''
Converted to Python 6/00 by Jason Petrone(jp@demonseed.net)


/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 *  movelight.c
 *  This program demonstrates when to issue lighting and
 *  transformation commands to render a model with a light
 *  which is moved by a modeling transformation (rotate or
 *  translate).  The light position is reset after the modeling
 *  transformation is called.  The eye position does not change.
 *
 *  A sphere is drawn using a grey material characteristic.
 *  A single light source illuminates the object.
 *
 *  Interaction:  pressing the left mouse button alters
 *  the modeling transformation (x rotation) by 30 degrees.
 *  The scene is then redrawn with the light in a new position.
 */

'''

import sys

try:
  from OpenGL.GLUT import *
  from OpenGL.GL import *
  from OpenGL.GLU import *
except:
  print '''
ERROR: PyOpenGL not installed properly.
        '''
  sys.exit()


spin = 0

#  Initialize material property, light source, lighting model,
#  and depth buffer.
def init():
   glClearColor (0.0, 0.0, 0.0, 0.0)
   glShadeModel (GL_FLAT)
   glEnable(GL_LIGHTING)
   glEnable(GL_LIGHT0)
   glEnable(GL_LIGHT1)
   glEnable(GL_LIGHT2)
   glEnable(GL_DEPTH_TEST)

gx=3;
gy=0;
gz=5;
def vec(*args):
   return (GLfloat * len(args))(*args)

#  Here is where the light position is reset after the modeling
#  transformation (glRotated) is called.  This places the
#  light at a new position in world coordinates.  The cube
#  represents the position of the light.
rot1 = 0
rot2 = 0
def Timer(value):
    global rot1,rot2
    rot1+=1
    rot2+=1
    glutPostRedisplay()
    glutTimerFunc(10, Timer, 0);


VEC1 = [1,0,1,1]
VEC2 = [1,1,1,1]

def display():
   position =  [0.0, 0.0, 1.5, 1.0]
   materialColor = {1.0, 1.0, 0.0, 1.0};
   global gx,gy,gz,rot1,rot2
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()
   gluLookAt (gx, gy, gz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)


   glPushMatrix ()
   glRotated (spin, 1.0, 0.0, 0.0)
   glLightfv (GL_LIGHT0, GL_POSITION, position)

   glTranslatef (0.0, 0.0, 1.5)
   glDisable (GL_LIGHTING)
   glColor3f (0.0, 0.0, 1.0)
   glutWireCube (0.1)
   glEnable (GL_LIGHTING)
   glPopMatrix ()

   glLightfv (GL_LIGHT1, GL_DIFFUSE, VEC1)
   glLightfv (GL_LIGHT2, GL_SPECULAR, VEC2)


   glPushMatrix ()
   glRotated (rot1, 1.0, 0.0, 0.0)
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, vec(1.0, 1.0, 0.0, 1.0) );
   glutSolidTorus (0.275, 0.85, 8, 35)
   glPopMatrix ()

   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, vec(0.3, 0.3, 0.3, 1.0) );
   glutSolidSphere (0.2,35, 35)

   glPushMatrix ()
   glRotated (rot2, 0.0, 1.0, 0.0)
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, vec(1.0, 0.0, 0.0, 1.0) );
   glutSolidTorus (0.1, 0.40, 8, 35)

   glPopMatrix ()

   glFlush ()

def reshape (w, h):
   glViewport (0, 0, w, h)
   glMatrixMode (GL_PROJECTION)
   glLoadIdentity()
   gluPerspective(40.0, w/h, 1.0, 200.0)
   glMatrixMode(GL_MODELVIEW)
   glLoadIdentity()

def mouse(button, state, x, y):
   global spin
   if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
       spin = (spin + 30) % 360
       glutPostRedisplay()

def keyboard(key, x, y):
   global gx,gy,gz
   if key == chr(27):
       sys.exit(0)
   if key == '8':
       gy+=1
       glutPostRedisplay()
   if key == '2':
       gy-=1
       glutPostRedisplay()
   if key == '4':
       gx-=1
       glutPostRedisplay()
   if key == '6':
       gx+=1
       glutPostRedisplay()
   if key == '7':
       gz+=1
       glutPostRedisplay()
   if key == '1':
       gz-=1
       glutPostRedisplay()


glutInit(sys.argv)
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB |GLUT_DEPTH)
glutInitWindowSize (500, 500);
glutInitWindowPosition(100, 100)
glutCreateWindow("movelight")
init()
glutDisplayFunc(display)
glutReshapeFunc(reshape)
glutMouseFunc(mouse)
glutTimerFunc(1, Timer, 0);
glutKeyboardFunc(keyboard)
glutMainLoop()
