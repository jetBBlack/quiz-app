#include "MyApp.h"
#include "file_handle.h"


#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 720

Question questions[10];
MyApp::MyApp() {
  ///
  /// Create our main App instance.
  ///
  app_ = App::Create();

  ///
  /// Create a resizable window by passing by OR'ing our window flags with
  /// kWindowFlags_Resizable.
  ///
  window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
    false, kWindowFlags_Titled | kWindowFlags_Resizable);

  ///
  /// Tell our app to use 'window' as our main window.
  ///
  /// This call is required before creating any overlays or calling App::Run
  ///
  app_->set_window(*window_.get());

  ///
  /// Create our HTML overlay-- we don't care about its initial size and
  /// position because it'll be calculated when we call OnResize() below.
  ///
  overlay_ = Overlay::Create(*window_.get(), 1, 1, 0, 0);

  ///
  /// Force a call to OnResize to perform size/layout of our overlay.
  ///
  OnResize(window_->width(), window_->height());

  ///
  /// Load a page into our overlay's View
  ///
  overlay_->view()->LoadURL("file:///app.html");
  
  ///
  /// Register our MyApp instance as an AppListener so we can handle the
  /// App's OnUpdate event below.
  ///
  app_->set_listener(this);

  ///
  /// Register our MyApp instance as a WindowListener so we can handle the
  /// Window's OnResize event below.
  ///
  window_->set_listener(this);

  ///
  /// Register our MyApp instance as a LoadListener so we can handle the
  /// View's OnFinishLoading and OnDOMReady events below.
  ///
  overlay_->view()->set_load_listener(this);

  ///
  /// Register our MyApp instance as a ViewListener so we can handle the
  /// View's OnChangeCursor and OnChangeTitle events below.
  ///
  overlay_->view()->set_view_listener(this);
}

MyApp::~MyApp() {
}

void MyApp::Run() {
  app_->Run();
}

void MyApp::OnUpdate() {
  ///
  /// This is called repeatedly from the application's update loop.
  ///
  /// You should update any app logic here.
  ///
}

void MyApp::OnClose() {
}

void MyApp::OnResize(uint32_t width, uint32_t height) {
  ///
  /// This is called whenever the window changes size (values in pixels).
  ///
  /// We resize our overlay here to take up the entire window.
  ///
  overlay_->Resize(width, height);
}

void MyApp::OnFinishLoading(ultralight::View* caller,
                            uint64_t frame_id,
                            bool is_main_frame,
                            const String& url) {
  ///
  /// This is called when a frame finishes loading on the page.
  ///
}

std::string create_utf8_from_jsstring_ref(JSStringRef str) {
  // Get the maximum conversion length
  size_t buffer_size = JSStringGetMaximumUTF8CStringSize(str);

  if(buffer_size < 1) {
      // Check for 0 length
      return "";
  }

  // Allocate a buffer to store the data in
  char *buffer = new char[buffer_size];

  // Convert the string
  size_t real_size = JSStringGetUTF8CString(str, buffer, buffer_size);

  // Copy the buffer length into a std::string
  // This constructor takes the length without the null byte
  std::string ret(buffer, real_size - 1);

  // Clean up and return
  delete[] buffer;
  return ret;
}

JSValueRef saveScore(JSContextRef ctx, JSObjectRef function,
                        JSObjectRef thisObject, size_t argumentCount,
                        const JSValueRef arguments[], JSValueRef *exception)
{
  JSStringRef string_ref = JSValueToStringCopy(ctx, arguments[0], NULL);
  double size = JSStringGetLength(string_ref);
  std::string player_name = create_utf8_from_jsstring_ref(string_ref);
  // fstream save;
  // save.open("score.txt", fstream::app);
  // if (save.is_open())
  // {
  //   save << size << ": " << (int)arguments[1] << "\n";
  //   save.close();
  // }
  saveScore(player_name, (int)arguments[1]);
  return JSValueMakeNull(ctx);
}

void MyApp::OnDOMReady(ultralight::View* caller,
                       uint64_t frame_id,
                       bool is_main_frame,
                       const String& url) {

  ///
  /// This is called when a frame's DOM has finished loading on the page.
  ///
  /// This is the best time to setup any JavaScript bindings.
  ///
  Ref<JSContext> context = caller->LockJSContext();
  JSContextRef ctx = context.get();
  JSObjectRef arrObject = JSObjectMakeArray(ctx, 0, NULL, NULL);
 
  JSStringRef question = JSStringCreateWithUTF8CString("question");
  JSStringRef opt1 = JSStringCreateWithUTF8CString("opt1");
  JSStringRef opt2 = JSStringCreateWithUTF8CString("opt2");
  JSStringRef opt3 = JSStringCreateWithUTF8CString("opt3");
  JSStringRef opt4 = JSStringCreateWithUTF8CString("opt4");
  JSStringRef answer = JSStringCreateWithUTF8CString("answer");
 
  
  for (int32_t i = 0; i < 10; i++ ){
    //questions[i].question = "What does CSS stand for?";
    questions[i].setObjProperty(i);
    JSObjectRef myObj = JSObjectMake(ctx, NULL, NULL);
    JSObjectSetProperty(ctx, myObj, question, JSValueMakeString(ctx, JSStringCreateWithUTF8CString(questions[i].question.c_str())), kJSPropertyAttributeNone, NULL);
    JSObjectSetProperty(ctx, myObj, opt1, JSValueMakeString(ctx, JSStringCreateWithUTF8CString(questions[i].option1.c_str())), kJSPropertyAttributeNone, NULL);
    JSObjectSetProperty(ctx, myObj, opt2, JSValueMakeString(ctx, JSStringCreateWithUTF8CString(questions[i].option2.c_str())), kJSPropertyAttributeNone, NULL);
    JSObjectSetProperty(ctx, myObj, opt3, JSValueMakeString(ctx, JSStringCreateWithUTF8CString(questions[i].option3.c_str())), kJSPropertyAttributeNone, NULL);
    JSObjectSetProperty(ctx, myObj, opt4, JSValueMakeString(ctx, JSStringCreateWithUTF8CString(questions[i].option4.c_str())), kJSPropertyAttributeNone, NULL);
    JSObjectSetProperty(ctx, myObj, answer, JSValueMakeString(ctx, JSStringCreateWithUTF8CString(questions[i].answer.c_str())), kJSPropertyAttributeNone, NULL);
    JSObjectSetPropertyAtIndex(ctx, arrObject, i, myObj, NULL);
  }
    
  
  JSRetainPtr<JSStringRef> str = adopt(JSStringCreateWithUTF8CString("getQuestion"));
  JSValueRef func = JSEvaluateScript(ctx, str.get(), 0, 0, 0, 0);

  if(JSValueIsObject(ctx, func)){

    JSObjectRef funObject = JSValueToObject(ctx, func, 0);
    JSValueRef args[] = { arrObject };
    //JSValueRef args[] = { (JSValueRef)arrObject };
    //size_t num_args = sizeof(args) / sizeof(JSValueRef *);
    JSValueRef exception = 0;
    JSValueRef result = JSObjectCallAsFunction(ctx, funObject, 0, 1, args, &exception);
    if (exception)
    {
      // Handle any exceptions thrown from function here.
    }
  }
  JSStringRef name = JSStringCreateWithUTF8CString("saveScore");

  JSObjectRef function = JSObjectMakeFunctionWithCallback(ctx, name,
                                                      saveScore);
  JSObjectRef globalObj = JSContextGetGlobalObject(ctx);
  JSObjectSetProperty(ctx, globalObj, name, function, 0, 0);
  
}

void MyApp::OnChangeCursor(ultralight::View* caller,
                           Cursor cursor) {
  ///
  /// This is called whenever the page requests to change the cursor.
  ///
  /// We update the main window's cursor here.
  ///
  window_->SetCursor(cursor);
}

void MyApp::OnChangeTitle(ultralight::View* caller,
                          const String& title) {
  ///
  /// This is called whenever the page requests to change the title.
  ///
  /// We update the main window's title here.
  ///
  window_->SetTitle("QUIZ APP!");
}
