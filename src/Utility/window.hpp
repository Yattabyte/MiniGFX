#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

// Forward Declarations
struct GLFWwindow;

/** A representation of a GLFW window object. */
class Window {
    public:
    // Public (De)Constructors
    /** Destroy this window. */
    ~Window();
    /** Construct a window with a given size.
    @param  width   the width to make the window.
    @param  height  the height to make the window. */
    Window(const int& width, const int& height) noexcept;
    /** Default copy constructor. */
    Window(const Window& o) = delete;
    /** Default move constructor. */
    Window(Window&& o) noexcept;

    // Public Operators
    /** Default copy-assignment operator. */
    Window& operator=(const Window& p) = delete;
    /** Default move-assignment operator. */
    Window& operator=(Window&& p) noexcept;

    // Public Methods
    /** Check whether or not this window exists and is valid.
    @return     true if window exists, false otherwise. */
    bool exists() const noexcept;
    /** Retrieve the underlying window object pointer.
    @return     the GLFWwindow pointer. */
    GLFWwindow* pointer() const noexcept;
    /** Retrieve the window's width.
    @return     the width of the window. */
    int getWidth() const noexcept;
    /** Retrieve the window's height.
    @return     the height of the window. */
    int getHeight() const noexcept;

    private:
    // Private Attributes
    /** The window width. */
    int m_width = 1;
    /** The window height. */
    int m_height = 1;
    /** The GLFW window object pointer. */
    GLFWwindow* m_window = nullptr;
};

#endif // WINDOW_HPP