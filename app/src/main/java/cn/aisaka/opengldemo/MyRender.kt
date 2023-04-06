package cn.aisaka.opengldemo

import android.graphics.ImageFormat
import android.opengl.GLSurfaceView.Renderer
import androidx.camera.core.ImageProxy
import java.nio.ByteBuffer
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyRender:Renderer {

    private val mNativeContextHandle: Long = 0

    init {
        System.loadLibrary("Demo")
    }
    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {

        native_OnCreate()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        native_onSurfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        native_OnDrawFrame()
    }

    fun onSurfaceDestroyed(){

    }

    fun updateRGBAImage(width:Int,height: Int,data:ByteArray){
        native_UpdateFrame(data,width,height,ImageFormat.FLEX_RGBA_8888)
    }

    external fun native_OnCreate()

    external fun native_OnDrawFrame()

    external fun native_onSurfaceChanged(width: Int, height: Int)

    external fun native_UpdateFrame(data:ByteArray,width: Int, height: Int,format:Int)

    external fun native_onSurfaceDestroyed()
}