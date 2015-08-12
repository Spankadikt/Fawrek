using System;
using System.Windows.Forms;
using Tao.OpenGl;
using Tao.Platform.Windows;
using Fawrek.Wrapper;
using System.Windows.Media;

namespace Fawrek.Editor.UserControls
{
    class ViewportControl : SimpleOpenGlControl
    {
        private double m_dScaleX = 1.0;
        private double m_dScaleY = 1.0;

        public ViewportControl()
        {
            InitializeContexts();

            CompositionTarget.Rendering += CompositionTarget_Rendering;
        }

        void CompositionTarget_Rendering(object sender, EventArgs e)
        {
            if (FawrekEngine.fawrekPtr != null && FawrekEngine.fawrekPtr != IntPtr.Zero)
            {
                Draw();
            }
        }

        protected override void OnHandleDestroyed(EventArgs e)
        {
            CompositionTarget.Rendering -= CompositionTarget_Rendering;

            if (FawrekEngine.fawrekPtr != null && FawrekEngine.fawrekPtr != IntPtr.Zero)
            {
                Fawrek.Wrapper.Wrapper.RunFawrekDelete(FawrekEngine.fawrekPtr);
            }

            base.OnHandleDestroyed(e);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            if (FawrekEngine.fawrekPtr != null && FawrekEngine.fawrekPtr != IntPtr.Zero)
            {
                MakeCurrent();
                Fawrek.Wrapper.Wrapper.RunFawrekRender(FawrekEngine.fawrekPtr);
                SwapBuffers();
            }
            else
            {
                base.OnPaint(e);
            }
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
