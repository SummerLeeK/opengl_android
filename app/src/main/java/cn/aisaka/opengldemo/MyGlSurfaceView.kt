package cn.aisaka.opengldemo

import android.content.Context
import android.opengl.GLSurfaceView
import android.os.Build
import android.view.Surface
import android.view.SurfaceControl
import android.view.SurfaceHolder

class MyGlSurfaceView(context: Context) : GLSurfaceView(context) {

    private var render: MyRender? = null

    init {

    }

    fun setCusRender(render: MyRender) {
        this.render = render
        setEGLContextClientVersion(2)
        setRenderer(render)
        renderMode = RENDERMODE_CONTINUOUSLY
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        super.surfaceCreated(holder)

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
                holder.surface.setFrameRate(120F, Surface.FRAME_RATE_COMPATIBILITY_FIXED_SOURCE)
            }
        }
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        super.surfaceDestroyed(holder)
        render?.onSurfaceDestroyed()
    }
}