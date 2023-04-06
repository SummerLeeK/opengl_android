package cn.aisaka.opengldemo

import android.hardware.camera2.CaptureRequest
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.util.Range
import android.util.Size
import android.widget.FrameLayout
import androidx.camera.camera2.interop.Camera2Interop
import androidx.camera.core.CameraSelector
import androidx.camera.core.ImageAnalysis
import androidx.camera.core.Preview
import androidx.camera.lifecycle.ProcessCameraProvider
import androidx.core.content.ContextCompat
import java.io.File
import java.io.FileOutputStream
import java.io.OutputStream
import java.nio.ByteBuffer
import java.util.concurrent.Executors

class MainActivity : AppCompatActivity() {
   lateinit var frameLayout:FrameLayout
   lateinit var glSurfaceView: MyGlSurfaceView
   lateinit var myRender: MyRender
    lateinit var output: OutputStream
    lateinit var file: File
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        frameLayout=findViewById(R.id.framelayout)


        glSurfaceView=MyGlSurfaceView(this)

        myRender=MyRender()

        glSurfaceView.setCusRender(myRender)

        frameLayout.addView(glSurfaceView)
        file = File(
            getExternalFilesDir(null),
            "frame.rgba"
        )
        output = FileOutputStream(file)

//        val cameraProviderFuture = ProcessCameraProvider.getInstance(this)
//        cameraProviderFuture.addListener(Runnable {
//
//            val cameraProvider = cameraProviderFuture.get()
//
//
//            val cameraSelector = CameraSelector.DEFAULT_BACK_CAMERA
//            var builder = ImageAnalysis.Builder()
//            val imageAnalysis = builder
//                .setTargetResolution(Size(720, 1280))
//                .setOutputImageFormat(ImageAnalysis.OUTPUT_IMAGE_FORMAT_RGBA_8888)
//                .build()
//
//            var count = 0
//            imageAnalysis.setAnalyzer(
//                Executors.newSingleThreadExecutor(),
//                ImageAnalysis.Analyzer { image ->
//                    val startTime = System.currentTimeMillis()
//                    count++
//
//                    val length=image.planes[0].buffer.remaining()
//                    val byteArray=ByteBuffer.allocate(length)
//                    byteArray.put(image.planes[0].buffer)
////                    if (count==10){
////                        saveYUVFile(byteArray.array())
////                    }
//                    myRender.updateRGBAImage(image.width,image.height,byteArray.array())
//                    image.close()
//                    Log.e("ImageAnalysis", "耗时 ${System.currentTimeMillis() - startTime}")
//
//                })
////            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
////                val cameraManager = getSystemService(Context.CAMERA_SERVICE) as CameraManager
////                cameraManager.cameraIdList.forEach {
////                    var supportedUtilSize: List<Size?>? = ArrayList()
////                    val characteristics: CameraCharacteristics =
////                        cameraManager.getCameraCharacteristics(it) // 0和1
////
////                    val configs = characteristics.get(CameraCharacteristics.SCALER_STREAM_CONFIGURATION_MAP)
////
////                    supportedUtilSize = Arrays.asList(*configs!!.getOutputSizes(ImageFormat.YUV_420_888))
////                    Log.e("HHH","${it}\t${JSON.toJSONString(supportedUtilSize)}")
////                    Log.e("HHH","fps\t${it}\t${JSON.toJSONString(configs!!.highSpeedVideoFpsRanges)}")
////
////                }
////            }
//            try {
//                cameraProvider.unbindAll()
//                cameraProvider.bindToLifecycle(this, cameraSelector,imageAnalysis)
//            } catch (e: Exception) {
//                Log.e("HHH", e.toString())
//            }
//
//        }, ContextCompat.getMainExecutor(this))
    }

    fun saveYUVFile(i420Frame: ByteArray) {
        val length =i420Frame.size
        output.write(i420Frame, 0, length)
    }
}