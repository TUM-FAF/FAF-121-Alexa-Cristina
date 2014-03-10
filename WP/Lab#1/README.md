 
Laboratory Work #1
==================
 
Title
------
 Window. Window handling. Basic window's form elements.
 
## Contents:

* Win32 API
* Win32 API
* GIT
* Programming Style Guidelines
* Window
* Button
* Text Input
* Text
 
##Objectives:
 + Understanding and using CLI (basic level)
 + Administration of a remote linux machine using SSH
 + Ability to work remotely (remote code editing)
 + Ability to work with VCS
 
## Executed Tasks:
  **Mandatory Tasks:**

* Create a Windows application
* Choose a _Programming Style Guideline_ that you'll follow
*  Add 2 buttons to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
*  Add 2 text inputs to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
*  Add 2 text elements to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
 
  **Tasks With Points:**  

- Make elements to fit window on resize **(1 pt)** _(hint: you can limit minimal window width and height)_    
- Make elements to interact or change other elements (1 pt for 2 different interactions) **(0-2 pt)** _(ex. on button click, change text element color or position)_
-  Change behavior of different window actions (at least 3). For ex.: on clicking close button, move window to a random location on display's working space **(1 pt)**
-  Write your own PSG (you can take existent one and modify it) and argue why it is better (for you) **(1 pt)**
 
  **Additional Tasks:**
  
- Additional taks done for fun
 
## Theoretical Work:
 
The programming language that I'll use will be C++. As I had to choose a PSG, I've chosen the [USC Aerial Robotics Programming Style Guide (C++)](https://github.com/uscrs-art/uscrs-art/wiki). I made some little changes that you can find in the [PSG_changes] file. 

After struggling a bit with understanding the new concepts of window programming, I understood what is the role of the handle for an object. The handle is Also, the idea of receiving multiple messages in a queue and calling functions using these specific messages.
 

##Practical Work:
####Create A Windows application

 I just followed the guideline from the WP tasks set. It worked. 

#### Choose a Programming Style Guidline that you'll follow:

 [USC Aerial Robotics Programming Style Guide (C++)](https://github.com/uscrs-art/uscrs-art/wiki). I made some little changes that you can find in the  file.

####Add 2 buttons to window: one with default styles, one with custom styles (size, background, text color, font family, font size)

 For the default button I used the system's default font. For the other one I createad another font:

	FontCustom = CreateFont(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, FALSE,
                            0, 0, 0, 0, "Arial");

And there's also other button that I created another font specifically for it. The way I set the font, background and text color was by making the style of the button `BS_OWNERDRAW`. Afterwards I set the necessary properties of the button for the ```WM_OWNERDRAW```:.


	SelectObject(item->hDC, FontCustom);
	FillRect(item->hDC, &item->rcItem, WHITE_BRUSH);  
	SelectObject(item->hDC, WHITE_BRUSH);  
	SetTextColor(item->hDC, clrGreenish);  
	SelectObject(item->hDC, CreatePen(PS_ENDCAP_ROUND, 2, clrGreenish));  
	  if ((item->itemState & ODS_SELECTED)==TRUE)  
	  {    
		 SetTextColor(item->hDC, 0);  
		 SelectObject(item->hDC, CreateSolidBrush(clrGreenish));    
		 SelectObject(item->hDC, CreatePen(PS_SOLID, 1, clrGreenish));  
	  }
	RoundRect(item->hDC, item->rcItem.left, item->rcItem.top, item->rcItem.right,
	            item->rcItem.bottom, 10, 10);
	SetBkMode(item->hDC, TRANSPARENT);
	int len = GetWindowTextLength(item->hwndItem);
	LPSTR lpBuff = new char[len+1];
	GetWindowText(item->hwndItem, lpBuff, len+1);
	DrawText(item->hDC, lpBuff, len, &item->rcItem, DT_CENTER);

 
### Add 2 text inputs to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
 
For the text input with default styles it was easy to set it up. I needed just to know how to create the edit and set it according to function  parameters of `CreateWindowEx()`. The one with the custom style, was set by editing the case of message `WM_CTLCOLOREDIT` where I gave a background and text color. The font was set as for the button control. 
 
### Add 2 text elements to window: one with default styles, one with custom styles (size, background, text color, font family, font size)

The strategy with the control of text elements was similar with the ones for text input. There were some differentiations.

### Make elements to fit window on resize **(1 pt)**
 
I made this by mentioning the case `WM_SIZE` and calling the `MoveWindow()` function. In the function I set for each control the behavior needed. Also, I set the minimal window size using the case of message `WM_GETMINMAXINFO`, where I set the sizes of the structure `GETMAXINFO`.
 
#### Make elements to interact or change other elements (1 pt for 2 different interactions) **(0-2 pt)** _(ex. on button click, change text element color or position)_

The first interaction is that the text elements were filled in with the text from the edit control, when the respective button was pressed (the left button for the left controls, and the right button, respectively. The second interaction is cleaning all the text controls when pressing the button CLEAR
 
#### Change behavior of different window actions (at least 3). For ex.: on clicking close button, move window to a random location on display's working space **(1 pt)**
 
I changed the behavior of all System Buttons of the window. The `WM_CLOSE`, when pressed gives a MessageBox, which informs that the user is taking the wrong way. 
The `WM_MINIMIZE` actually maximizes the window in the whole system's display. 
And the `WM_MAXIMIZE`, gives a message in which it is asking the user weather he/she wants really to close the app. If the user presses YES then the windows gets the message `WM_CLOSE`, which closes the application
 
#### Write your own PSG (you can take existent one and modify it) and argue why it is better (for you) **(1 pt)**
 
The changes that I made to the [USC Aerial Robotics Programming Style Guide (C++)](https://github.com/uscrs-art/uscrs-art/wiki) are some simple ones. So I described them [here]().
  
### Conclusions:


During this laboratory work, I got more or less comfortable with event driven programming. I understood the deeper insight of how it is working. The way that the functions are used to change some features of the window was by sending messages to the main function and putting in the queue. Well, this was probably the most curious, because at first it was difficult for me to understand how does the Window Main Function does process all these messages, and that there are some messages that are not - queued.
 
An important  remark is that each object, beginning with the window made, can not be created without a handle. Also, the fact that it is used as an identifier for the system to be used in functions.

Another thing that was interesting for me to learn is the thing that the controls like buttons, edit elements and text elements are considered themselves as smaller windows -- subwindows. For each type of these controls was a specific way to customize them and set a specific style. Another interesting thing are the system flags that are used to set some particular features to a control. 

The fact that I had to use a PSG, made me enthusiastic about writing nice and compact code, using one of them. I cannot say though that the features and the guidelines made me perfectly comfortable with it, but I am still learning to make it better.