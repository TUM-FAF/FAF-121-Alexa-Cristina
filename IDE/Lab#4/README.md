# Interactive Development Environments Laboratory Work #4

## Web development IDEs/text editors:
  - Sublime Text 3

### Prerequisites:
  - Languages: Python
  - Technologies and Frameworks: Django

### Mandatory Tasks:
  I've chosen Django as I have a little experience with Python
  - Install chosen framework on your computer (or a remote server)
  This was easy. I installed Django for System Operator, I didn't use virtual environment for the project
  - Serve a static page with your name on it at address `/me.html` or `/me`
    ![Example](/media/alexa/F8084D3C084CFB60/Projects/WP_IDE/IDE/Lab#4/screenshot_lab4.png)
  - Serve a bootstrap form. It should have at least one field (ex. name). On submitting this form save data (in database or files or session or localStorage or whatever you want). Output a list of data from all previously submits.
This specific task, I have done it in q different way. Actually, the form that was served was in Django, but I used also, bootstrap also, but not for creating font specifically.

### Tasks With Points:
  - Use framework command line to generate project files (2pt)
    I used python command line, I even used it to manipulate models.
  - Save data submitted through form into database (1pt)
    I did this using db.sqlite3(). Although I am not pretty confortable with databases yet. 
  - Create and use database seed (2pt)
    I used databases seed in my application, but I am not sure that I really understood how it works. 
  - Migrations (one of):
    - Use a relational database. Alter form fields and database structure (ex. add one more input field to form and add a column for it in your database). Create a migration for it. (2pt)
  - Use a different from default HTML templating engine (1pt)
    This is what I did with Bootstrap, actually.

Conclusions: 
  During, this Laboratory works, I consulted two sites most of all.
  These are:
  * [Django Official Documentation](https://docs.djangoproject.com/en/dev/) 
  This helped me to make some modifications on the later release of Django, because I used a dev's version.
  * [Tango with Django Tutorial Site](http://www.tangowithdjango.com/book/chapters)
  Basically, all the tasks that I did are from this book. 
  It was not easy to learn how to do a task or another, and I tried to do the tasks by myself, even I had the tutorial guide helping me, in order to make me think how data and code works everywhere in my project. I got more comfortable with python and with django as well. 