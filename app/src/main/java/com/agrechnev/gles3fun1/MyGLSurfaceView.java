package com.agrechnev.gles3fun1;

import android.content.Context;
import android.opengl.GLSurfaceView;

/**
 * Created by Oleksiy Grechnyev on 1/17/2017.
 */

public class MyGLSurfaceView extends GLSurfaceView {

    private final MyGLRenderer renderer;

    // Constructor: version + renderer
    public MyGLSurfaceView(Context context) {
        super(context);

        // GLES 3.0 or above !
        setEGLContextClientVersion(3);

        renderer = new MyGLRenderer();
        setRenderer(renderer);
    }
}
