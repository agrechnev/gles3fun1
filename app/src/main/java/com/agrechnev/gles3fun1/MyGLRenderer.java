package com.agrechnev.gles3fun1;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by Oleksiy Grechnyev on 1/17/2017.
 * My rendered class, calls JNI functions
 */

public class MyGLRenderer implements GLSurfaceView.Renderer {
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        JNILibrary.init();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        JNILibrary.resize(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        JNILibrary.draw();
    }
}
