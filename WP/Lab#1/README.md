 +# Laboratory Work #1
 +## Title
 +  Window. Window handling. Basic window's form elements
 
 +##Contents
 
 +*Win32 API
 +*Win32 API
 +*GIT
 +*Programming Style Guidelines
 +*Window
 +*Button
 +*Text Input
 +*Text
 
 ## Objectives:
 + Understanding and using CLI (basic level)
 + Administration of a remote linux machine using SSH
 + Ability to work remotely (remote code editing)
 + Ability to work with VCS
 
 ## Executed Tasks:
  **Mandatory Tasks:**
 +  Create a Windows application
 +  Choose a _Programming Style Guideline_ that you'll follow
 +   Add 2 buttons to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
 +  Add 2 text inputs to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
 +  Add 2 text elements to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
  **Tasks With Points:**
 +  Make elements to fit window on resize **(1 pt)** _(hint: you can limit minimal window width and height)_
 +  Make elements to interact or change other elements (1 pt for 2 different interactions) **(0-2 pt)** _(ex. on button click, change text element color or position)_
 +  Change behavior of different window actions (at least 3). For ex.: on clicking close button, move window to a random location on display's working space **(1 pt)**
 +  Write your own PSG (you can take existent one and modify it) and argue why it is better (for you) **(1 pt)**
  **Additional Tasks:**
 + Additional taks done for fun
 +
 +## Theoretical Work:
 +
 + The programming language that I'll use will be C++. As I had to choose a PSG, I've chosen the [USC Aerial Robotics Programming Style Guide (C++)](https://github.com/uscrs-art/uscrs-art/wiki). I made some little changes that you can find in the [PSG_changes] file. 

 + After struggling a bit with understanding the new concepts of window programming, I understood what is the role of the handle for an object. The handle is Also, the idea of receiving multiple messages in a queue and calling functions using these specific messages.
 
 ##Practical Work:
 +#Create A Windows application
 + I just followed the guideline from the WP tasks set. It worked. 
 +# Choose a Programming Style Guidline that you'll follow:
 + [USC Aerial Robotics Programming Style Guide (C++)](https://github.com/uscrs-art/uscrs-art/wiki). I made some little changes that you can find in the [PSG_changes] file.
 +#Add 2 buttons to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
 + For the default button I used the system's default font. For the other one I createad another font:
 '''
 FontCustom = CreateFont(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, FALSE,
                              0, 0, 0, 0, "Arial");
 '''
  And there'is also other button that I created another font specifically for it. The way I set the font, background and text color was set by making the style of the button "BS_OWNERDRAW". Afterwards in the callback function I set the necessary properties of the button.
 +'''
 +SelectObject(item->hDC, FontCustom);
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
 '''
 
 +### Add 2 text inputs to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
 
 
 
 +### Add 2 text elements to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
 
 +_todo_
 
 +### Make elements to fit window on resize **(1 pt)**
 
 +_todo_
 
 +### Make elements to interact or change other elements (1 pt for 2 different interactions) **(0-2 pt)** _(ex. on button click, change text element color or position)_

 +_todo_
 
 +### Change behavior of different window actions (at least 3). For ex.: on clicking close button, move window to a random location on display's working space **(1 pt)**
 
 +_todo_
 
 +### Write your own PSG (you can take existent one and modify it) and argue why it is better (for you) **(1 pt)**
 
 +I've chosen the Robo
 
 +### Additional taks done for fun
 
 
 +## Conclusions:
 
