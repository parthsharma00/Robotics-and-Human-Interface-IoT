# Import required Libraries
from tkinter import *
from PIL import Image, ImageTk
import cv2
import numpy as np
# Create an instance of TKinter Window or frame
win= Tk()

# Set the size of the window
win.geometry()# Create a Label to capture the Video frames
win.title("Selfie")
win.config(bg="skyblue")
label =Label(win)
label.grid(row=0, column=0)
labelGRAY =Label(win)
labelGRAY.grid(row=0, column=1)



cap= cv2.VideoCapture(0)

# Define function to show frame
def show_frames():
      # Get the latest frame and convert into Image
      cv2image= cv2.cvtColor(cap.read()[1],cv2.COLOR_BGR2RGBA)
      img = Image.fromarray(cv2image)
      # Convert image to PhotoImage
      imgtk = ImageTk.PhotoImage(image = img)
      label.imgtk = imgtk
      label.configure(image=imgtk)
      # Repeat after an interval to capture continiously
      label.after(10, show_frames)

def gray():
      cv2image= cv2.cvtColor(cap.read()[1],cv2.COLOR_BGR2GRAY)
      img = Image.fromarray(cv2image)
      imgtk = ImageTk.PhotoImage(image = img)
      labelGRAY.imgtk = imgtk
      labelGRAY.configure(image=imgtk)

def blur():
      imgBlur = cv2.GaussianBlur(cap.read()[1],(15,15),0)
      img = Image.fromarray(imgBlur)
      imgtk = ImageTk.PhotoImage(image = img)
      labelGRAY.imgtk = imgtk
      labelGRAY.configure(image=imgtk)
def canny():
      imgCanny = cv2.Canny(cap.read()[1],150,200)
      img = Image.fromarray(imgCanny)
      imgtk = ImageTk.PhotoImage(image = img)
      labelGRAY.imgtk = imgtk
      labelGRAY.configure(image=imgtk)
def dialate():
      kernel = np.ones((5,5),np.uint8)
      imgCanny = cv2.Canny(cap.read()[1],150,200)
      imgDialation = cv2.dilate(cap.read()[1],kernel,iterations=1)
      img = Image.fromarray(imgCanny)
      imgtk = ImageTk.PhotoImage(image = img)
      labelGRAY.imgtk = imgtk
      labelGRAY.configure(image=imgtk)
def erode():
      kernel=np.ones((5,5),np.uint8)
      imgCanny = cv2.Canny(cap.read()[1],150,200)
      imgDialation = cv2.dilate(imgCanny,kernel,iterations=1)
      imgEroded = cv2.erode(cap.read()[1],kernel,iterations=1)
      img = Image.fromarray(imgCanny)
      imgtk = ImageTk.PhotoImage(image = img)
      labelGRAY.imgtk = imgtk
      labelGRAY.configure(image=imgtk)
      
def update_hsv(h, s, v):
            #global img_hsv
            img_hsv = cv2.cvtColor(cap.read()[1], cv2.COLOR_BGR2HSV)
            img_hsv[:, :, 0] = np.clip(img_hsv[:, :, 0], 0, h)
            img_hsv[:, :, 1] = np.clip(img_hsv[:, :, 1], 0, s)
            img_hsv[:, :, 2] = np.clip(img_hsv[:, :, 2], 0, v)
            img_bgr = cv2.cvtColor(img_hsv, cv2.COLOR_HSV2BGR)
            img = Image.fromarray(img_bgr)
            imgtk = ImageTk.PhotoImage(image = img)
            labelGRAY.imgtk = imgtk
            labelGRAY.configure(image=imgtk)

def update_size(h,w):
        imgResize=cv2.resize(cap.read()[1],(h,w))
        #cv2.imshow(" Resize",np.hstack((imgResize,imgResize,imgResize,imgResize)))
        img = Image.fromarray(imgResize)
        imgtk = ImageTk.PhotoImage(image = img)
        labelGRAY.imgtk = imgtk
        labelGRAY.configure(image=imgtk)
        
        """roi=frame[200:530, 120:320]
        imgroi=cv2.cvtColor(roi, cv2.COLOR_BGR2RGB)
        cv2.imshow(" roi",imgroi)
        print(frame.shape)
        imgResize = cv2.resize(frame,(1000,500))
        print(imgResize.shape) 
        imgCropped = frame[46:119,352:495]
        cv2.imshow("Image",frame)
        cv2.imshow("Image Resize",imgResize)
        cv2.imshow("Image Cropped",imgCropped)"""


tool_bar  =  Frame(win,  width=180,  height=185,  bg='grey')
tool_bar.grid(row=2,  column=0,  padx=5,  pady=5)
tool_bar1  =  Frame(win,  width=180,  height=185,  bg='grey')
tool_bar1.grid(row=3,  column=0,  padx=5,  pady=5)
tool_bar2  =  Frame(win,  width=180,  height=185,  bg='grey')
tool_bar2.grid(row=2,  column=1,  padx=5,  pady=5)

Button1 = Button(tool_bar, text = "Gray", command = gray)
Button1.grid(row=0, column=0,padx=5,  pady=5,  sticky='w'+'e'+'n'+'s')
Button2 = Button(tool_bar, text = "Blur", command = blur)
Button2.grid(row=0, column=1,padx=5,  pady=5,  sticky='w'+'e'+'n'+'s')
Button3 = Button(tool_bar, text = "Canny", command =canny)
Button3.grid(row=0, column=2)
Button4 = Button(tool_bar, text = "Dialate", command = dialate)
Button4.grid(row=0, column=3,padx=5,  pady=5,  sticky='w'+'e'+'n'+'s')
Button5 = Button(tool_bar, text = "Erode", command = erode)
Button5.grid(row=0, column=4,padx=5,  pady=5,  sticky='w'+'e'+'n'+'s')

label6 = Label(tool_bar2, text = "Size")
label6.grid(row=0, column=0,padx=5,  pady=5,  sticky='w'+'e'+'n'+'s')
height_slider = Scale(tool_bar2, from_=100, to=500, orient=HORIZONTAL, command=lambda h: update_size(int(h), width_slider.get()))
width_slider =  Scale(tool_bar2, from_=100, to=500, orient=HORIZONTAL, command=lambda w: update_size(height_slider.get(),int(w)))

height_slider.grid(row=0, column=1,padx=5,  pady=5,  sticky='w'+'e'+'n'+'s')
width_slider.grid(row=0, column=2,padx=5,  pady=5,  sticky='w'+'e'+'n'+'s')


hsv1=Label(tool_bar1, text="HSV").grid(row=1, column=0,padx=5,  pady=5,  sticky='w'+'e'+'n'+'s')
hue=Label(tool_bar1, text="HUE").grid(row=1, column=1,padx=5,  pady=5,  sticky='w'+'e'+'n'+'s')
sat=Label(tool_bar1, text="SATUR").grid(row=1, column=3,padx=5,  pady=5,  sticky='w'+'e'+'n'+'s')
val=Label(tool_bar1, text="VALUE").grid(row=1, column=5,padx=5,  pady=5,  sticky='w'+'e'+'n'+'s')
h_slider = Scale(tool_bar1, from_=0, to=180, orient=HORIZONTAL, command=lambda h: update_hsv(int(h), s_slider.get(), v_slider.get()))
s_slider = Scale(tool_bar1, from_=0, to=255, orient=HORIZONTAL, command=lambda s: update_hsv(h_slider.get(), int(s), v_slider.get()))
v_slider = Scale(tool_bar1, from_=0, to=255, orient=HORIZONTAL, command=lambda v: update_hsv(h_slider.get(), s_slider.get(), int(v)))
# Pack the scrollbars

h_slider.grid(row=1, column=2,padx=5,  pady=5,  sticky='w'+'e'+'n'+'s')
s_slider.grid(row=1, column=4,padx=5,  pady=5,  sticky='w'+'e'+'n'+'s')
v_slider.grid(row=1, column=6,padx=5,  pady=5,  sticky='w'+'e'+'n'+'s')
# Initialize the HSV values
#update_hsv(180, 255, 255)

def on_closing():
    cap.release()
    win.destroy()

win.protocol("WM_DELETE_WINDOW", on_closing)
show_frames()
win.mainloop()
