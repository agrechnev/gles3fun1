package com.agrechnev.gles3fun1;

/**
 * Created by Oleksiy Grechnyev on 1/17/2017.
 * The JNI calls are here
 */

public class JNILibrary {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    // OpenGLES-related methods, called from the MyRenderer wrapper
    public static native void init();
    public static native void resize(int width, int height);
    public static native void draw();

}
