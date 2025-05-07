#include "raymob.h"
#include <string.h>

void TakeAndroidScreenshot(const char *filename)
{
    jobject context = GetNativeLoaderInstance();
    if (context != NULL)
    {
        JNIEnv *env = AttachCurrentThread();
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, context);

        jfieldID screenshotField = (*env)->GetFieldID(env, nativeLoaderClass, "screenshotHelper", "Lcom/raylib/raymob/ScreenshotHelper;");
        jobject screenshotHelper = (*env)->GetObjectField(env, context, screenshotField);

        if (screenshotHelper != NULL)
        {
            jclass screenshotClass = (*env)->GetObjectClass(env, screenshotHelper);
            jmethodID method = (*env)->GetMethodID(env, screenshotClass, "takeScreenshot", "(Ljava/lang/String;)V");

            jstring jFilename = (*env)->NewStringUTF(env, filename);
            (*env)->CallVoidMethod(env, screenshotHelper, method, jFilename);
            (*env)->DeleteLocalRef(env, jFilename);
        }

        DetachCurrentThread();
    }
}
