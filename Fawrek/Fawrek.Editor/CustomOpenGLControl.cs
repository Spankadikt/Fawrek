using System;
using System.Windows.Forms;
using Tao.OpenGl;
using Tao.Platform.Windows;
using Fawrek.Wrapper;

namespace Fawrek.Editor
{
    class CustomOpenGLControl : SimpleOpenGlControl
    {
        private double m_dScaleX = 1.0;
        private double m_dScaleY = 1.0;

        IntPtr fawrekPtr;

        public CustomOpenGLControl()
        {
            Gl.glGetString(Gl.GL_VERSION);
            InitializeContexts();

            fawrekPtr = Fawrek.Wrapper.Wrapper.RunFawrekCreate();
            int initResult = Fawrek.Wrapper.Wrapper.RunFawrekInit(fawrekPtr);

        }

        protected override void OnPaint(PaintEventArgs e)
        {
            Gl.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

            Gl.glClear(Gl.GL_COLOR_BUFFER_BIT | Gl.GL_DEPTH_BUFFER_BIT);
            Gl.glLoadIdentity();

            /*Gl.glBegin(Gl.GL_TRIANGLES);
            Gl.glColor3f(1.0f, 0.0f, 0.0f); Gl.glVertex3f(-1.0f, -1.0f,  0.0f);
            Gl.glColor3f(0.0f, 1.0f, 0.0f); Gl.glVertex3f( 0.0f,  1.0f,  0.0f);
            Gl.glColor3f(0.0f, 0.0f, 1.0f); Gl.glVertex3f( 1.0f, -1.0f,  0.0f);
            Gl.glEnd();

            Gl.glFlush();*/

            //OpenGLDLLWrapper.Wrapper.RunTest();
            Fawrek.Wrapper.Wrapper.RunFawrekRender(fawrekPtr);

            SwapBuffers();
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            m_dScaleX = LogScaleX / 96.0;
            m_dScaleY = LogScaleY / 96.0;
            mIsInitialized = true;
        }

        private bool mIsInitialized = false;

        protected override void OnResize(EventArgs e)
        {
            if (mIsInitialized)
            {
                MakeCurrent();
                int iWidth = (int)m_dScaleX * Width;
                int iHeight = (int)m_dScaleY * Height;

                Gl.glViewport(0, 0, iWidth, iHeight);

                Gl.glMatrixMode(Gl.GL_PROJECTION);
                Gl.glLoadIdentity();
                Gl.glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

                Gl.glMatrixMode(Gl.GL_MODELVIEW);
                Gl.glLoadIdentity();
            }
        }

        protected override void OnPaintBackground(PaintEventArgs e)
        {
            return;
        }
    }
}
