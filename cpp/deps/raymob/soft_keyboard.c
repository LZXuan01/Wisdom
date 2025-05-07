/*
 *  raymob License (MIT)
 *
 *  Copyright (c) 2023-2024 Le Juez Victor
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include "raymob.h"
#include <string.h>



void ShowSoftKeyboard(void)
{
    jobject context = GetNativeLoaderInstance();

    if (context != NULL) {
        JNIEnv* env = AttachCurrentThread();
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, context);

        jfieldID softKeyboardField = (*env)->GetFieldID(env, nativeLoaderClass, "softKeyboard", "Lcom/raylib/raymob/SoftKeyboard;");
        jobject softKeyboard = (*env)->GetObjectField(env, context, softKeyboardField);

        if (softKeyboard != NULL) {
            jclass softKeyboardClass = (*env)->GetObjectClass(env, softKeyboard);
            jmethodID method = (*env)->GetMethodID(env, softKeyboardClass, "showKeyboard", "()V");
            (*env)->CallVoidMethod(env, softKeyboard, method);
        }

        DetachCurrentThread();
    }
}

void HideSoftKeyboard(void)
{
    jobject context = GetNativeLoaderInstance();

    if (context != NULL) {
        JNIEnv* env = AttachCurrentThread();
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, context);

        jfieldID softKeyboardField = (*env)->GetFieldID(env, nativeLoaderClass, "softKeyboard", "Lcom/raylib/raymob/SoftKeyboard;");
        jobject softKeyboard = (*env)->GetObjectField(env, context, softKeyboardField);

        if (softKeyboard != NULL) {
            jclass softKeyboardClass = (*env)->GetObjectClass(env, softKeyboard);
            jmethodID method = (*env)->GetMethodID(env, softKeyboardClass, "hideKeyboard", "()V");
            (*env)->CallVoidMethod(env, softKeyboard, method);
        }

        DetachCurrentThread();
    }
}

int GetLastSoftKeyCode(void)
{
    jobject context = GetNativeLoaderInstance();

    if (context != NULL) {
        JNIEnv* env = AttachCurrentThread();
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, context);

        jfieldID softKeyboardField = (*env)->GetFieldID(env, nativeLoaderClass, "softKeyboard", "Lcom/raylib/raymob/SoftKeyboard;");
        jobject softKeyboard = (*env)->GetObjectField(env, context, softKeyboardField);

        if (softKeyboard != NULL) {
            jclass softKeyboardClass = (*env)->GetObjectClass(env, softKeyboard);
            jmethodID method = (*env)->GetMethodID(env, softKeyboardClass, "getLastKeyCode", "()I");
            int value = (*env)->CallIntMethod(env, softKeyboard, method);
            DetachCurrentThread();
            return value;
        }

        DetachCurrentThread();
    }

    return 0;
}

unsigned short GetLastSoftKeyLabel(void)
{
    jobject context = GetNativeLoaderInstance();

    if (context != NULL) {
        JNIEnv* env = AttachCurrentThread();
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, context);

        jfieldID softKeyboardField = (*env)->GetFieldID(env, nativeLoaderClass, "softKeyboard", "Lcom/raylib/raymob/SoftKeyboard;");
        jobject softKeyboard = (*env)->GetObjectField(env, context, softKeyboardField);

        if (softKeyboard != NULL) {
            jclass softKeyboardClass = (*env)->GetObjectClass(env, softKeyboard);
            jmethodID method = (*env)->GetMethodID(env, softKeyboardClass, "getLastKeyLabel", "()C");
            unsigned short value = (*env)->CallCharMethod(env, softKeyboard, method);
            DetachCurrentThread();
            return value;
        }
    }

    return 0;
}

int GetLastSoftKeyUnicode(void)
{
    jobject context = GetNativeLoaderInstance();

    if (context != NULL) {
        JNIEnv* env = AttachCurrentThread();
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, context);

        jfieldID softKeyboardField = (*env)->GetFieldID(env, nativeLoaderClass, "softKeyboard", "Lcom/raylib/raymob/SoftKeyboard;");
        jobject softKeyboard = (*env)->GetObjectField(env, context, softKeyboardField);

        if (softKeyboard != NULL) {
            jclass softKeyboardClass = (*env)->GetObjectClass(env, softKeyboard);
            jmethodID method = (*env)->GetMethodID(env, softKeyboardClass, "getLastKeyUnicode", "()I");
            int value = (*env)->CallIntMethod(env, softKeyboard, method);
            DetachCurrentThread();
            return value;
        }
    }

    return 0;
}

char GetLastSoftKeyChar(void)
{
#define KEYCODE_ENTER    66
#define KEYCODE_DEL      67

    jobject context = GetNativeLoaderInstance();

    if (context != NULL) {
        char value = '\0';

        JNIEnv* env = AttachCurrentThread();
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, context);

        jfieldID softKeyboardField = (*env)->GetFieldID(env, nativeLoaderClass, "softKeyboard", "Lcom/raylib/raymob/SoftKeyboard;");
        jobject softKeyboard = (*env)->GetObjectField(env, context, softKeyboardField);

        if (softKeyboard != NULL) {
            jclass softKeyboardClass = (*env)->GetObjectClass(env, softKeyboard);

            jmethodID methodKeyCode = (*env)->GetMethodID(env, softKeyboardClass, "getLastKeyCode", "()I");
            int keyCode = (*env)->CallIntMethod(env, softKeyboard, methodKeyCode);

            if (keyCode != 0) {
                switch (keyCode) {
                    case KEYCODE_ENTER: {
                        value = '\n';
                    } break;
                    case KEYCODE_DEL: {
                        value = '\b';
                    } break;
                    default: {
                        jmethodID methodKeyUnicode = (*env)->GetMethodID(env, softKeyboardClass, "getLastKeyUnicode", "()I");
                        int u = (*env)->CallIntMethod(env, softKeyboard, methodKeyUnicode);
                        if (u > 0xFF) value = '?';
                        else value = (char) u;
                    }
                }
            }
        }

        DetachCurrentThread();

        return value;
    }

    return '\0';
}

void ClearLastSoftKey(void)
{
    jobject context = GetNativeLoaderInstance();

    if (context != NULL) {
        JNIEnv* env = AttachCurrentThread();
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, context);

        jfieldID softKeyboardField = (*env)->GetFieldID(env, nativeLoaderClass, "softKeyboard", "Lcom/raylib/raymob/SoftKeyboard;");
        jobject softKeyboard = (*env)->GetObjectField(env, context, softKeyboardField);

        if (softKeyboard != NULL) {
            jclass softKeyboardClass = (*env)->GetObjectClass(env, softKeyboard);
            jmethodID method = (*env)->GetMethodID(env, softKeyboardClass, "clearLastKeyEvent", "()V");
            (*env)->CallVoidMethod(env, softKeyboard, method);
        }

        DetachCurrentThread();
    }
}

void SoftKeyboardEditText(char* text, unsigned int size)
{
    char c = GetLastSoftKeyChar();
    if (c == '\0') return;

    unsigned int len = strlen(text);

    if (c == '\b' && len > 0)  {
        text[len-1] = '\0';
    } else if (c != '\b' && len < size) {
        text[len++] = c;
        text[len] = '\0';
    }

    ClearLastSoftKey();
}

// Mine function

const char* GetSoftKeyboardText(void) {
    jobject context = GetNativeLoaderInstance();
    static char textBuffer[1024] = {0}; // Static buffer to store text

    if (context != NULL) {
        JNIEnv* env = AttachCurrentThread();
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, context);

        jfieldID softKeyboardField = (*env)->GetFieldID(env, nativeLoaderClass, "softKeyboard", "Lcom/raylib/raymob/SoftKeyboard;");
        jobject softKeyboard = (*env)->GetObjectField(env, context, softKeyboardField);

        if (softKeyboard != NULL) {
            jclass softKeyboardClass = (*env)->GetObjectClass(env, softKeyboard);
            jmethodID method = (*env)->GetMethodID(env, softKeyboardClass, "getTextContent", "()Ljava/lang/String;");

            jstring jText = (jstring)(*env)->CallObjectMethod(env, softKeyboard, method);
            const char* cText = (*env)->GetStringUTFChars(env, jText, NULL);

            strncpy(textBuffer, cText, sizeof(textBuffer)-1);
            textBuffer[sizeof(textBuffer)-1] = '\0';

            (*env)->ReleaseStringUTFChars(env, jText, cText);
            (*env)->DeleteLocalRef(env, jText);
        }
        DetachCurrentThread();
    }

    return textBuffer;
}

void CreateEditText(int x, int y, int w, int h, const char* text, bool singleline)
{
    jobject context = GetNativeLoaderInstance();
    if (context != NULL)
    {
        JNIEnv* env = AttachCurrentThread();
        jclass cls = (*env)->GetObjectClass(env, context);
        jfieldID softKeyboardField = (*env)->GetFieldID(env, cls, "softKeyboard", "Lcom/raylib/raymob/SoftKeyboard;");
        jobject softKeyboard = (*env)->GetObjectField(env, context, softKeyboardField);

        jclass softKeyboardClass = (*env)->GetObjectClass(env, softKeyboard);
        jmethodID method = (*env)->GetMethodID(env, softKeyboardClass, "createEditText", "(IIIILjava/lang/String;Z)V");

        // 将 C 字符串转换为 Java 字符串
        jstring jText = (*env)->NewStringUTF(env, text);

        // 调用 Java 端的 createEditText 方法，并传递所有必要参数
        (*env)->CallVoidMethod(env, softKeyboard, method, x, y, w, h, jText, singleline);

        // 释放字符串局部引用
        (*env)->DeleteLocalRef(env, jText);
    }
    DetachCurrentThread();
}



void RemoveEditText()
{
    JNIEnv* env = AttachCurrentThread();
    jobject context = GetNativeLoaderInstance();
    jclass cls = (*env)->GetObjectClass(env , context);
    jfieldID softKeyboardField = (*env)->GetFieldID(env, cls, "softKeyboard", "Lcom/raylib/raymob/SoftKeyboard;");
    jobject softKeyboard = (*env)->GetObjectField(env, context, softKeyboardField);


    jclass skCls = (*env)->GetObjectClass(env , softKeyboard);
    jmethodID mid = (*env)->GetMethodID(env , skCls, "removeEditText", "()V");
    (*env)->CallVoidMethod(env , softKeyboard, mid);

    DetachCurrentThread();
}
