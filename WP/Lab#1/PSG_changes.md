
I made only a few changes to the PSG selected. So, they are:

The way of writing blocks for me will remain the same as I used it before, because it is easier to see the distinguish local variables and global ones. Also the code written in blocks is easier for me to read, and find when I need to look for a particular block of code. 

So, it looks like this: 

			switch (closeMessageBox)
	          {
	            case IDYES:
	              SendMessage(hwnd_, WM_DESTROY, 0, 0);
	              break;
	            case IDNO:
	              break;
	          }
	            return 0;


The parameters in the functions have an underscore at the end regardless of the way I've written them. I changed it because I got used at first with the Hungarian way of variable notations. In this way its easier to get know which are parameters and which are local variables of a specific function. 

E.g. `LRESULT CALLBACK windowProcedure (HWND hwnd_, UINT message_, WPARAM wParam_, LPARAM lParam_)`

I guess, it will suffer some other changes with writing more code. This is what I've got for now.