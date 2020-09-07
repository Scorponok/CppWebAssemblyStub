#include <emscripten.h>

// Javascript function that can be invoked from C++. Updates the output element to display the provided value.
EM_JS(void, update_output, (int value), {
    // It's in a C++ file, but this is javascript! If you modify this, you'll need to recompile the main.js file.

    // Set the text in the "output" element based on our current count.
    var element = document.getElementById('output');
    element.innerHTML = "Current count: " + value;

    // This would also work, if you just wanted to show the value with no text:
    // element.innerHTML = value;

    // If you pass text into a javascript function, you need to use the UTF8ToString function to make it a Javascript
    // String object.
});

// For our simple demo page, display an incrementing count, with the value stored here
static int output_count = 0;

// Resets the count to the specified value. Called from javascript, so must be extern; EMSCRIPTEN_KEEPALIVE stops LLVM
// from eliminating the function (because it isn't called elsewhere in this file) and automatically exports it, as if
// you added it to EXPORTED_FUNCTIONS.
extern "C" void EMSCRIPTEN_KEEPALIVE reset_count(int new_value)
{
    output_count = new_value;
}

// primary loop function - called repeatedly by emscripten if you invoke emscripten_set_main_loop in main()
void loop_func()
{
    // update our static count and update the web page to show the new count
    update_output(output_count++);
}

int main()
{
    // Start our emscripten execution loop
    // NOTE: because run_forever is set to 1, nothing else from main() will run after this function is called! All work
    // after this should be done in your loop_func implementation, which is called repeatedly by emscripten.
    constexpr int cycles_per_second = 2;
    constexpr int run_forever = 1;
    emscripten_set_main_loop(loop_func, cycles_per_second, run_forever);

    //
    // do not put any code here! It will never be executed! see comment above for details
    //

    return 0;
}