from django import forms
from models import Page, Category

class CategoryForm(forms.ModelForm):
	name = forms.CharField(max_length = 128, help_text = "Please enter the category name.")
	views = forms.IntegerField(widget = forms.HiddenInput(), initial = 0)
	likes = forms.IntegerField(widget = forms.HiddenInput(), initial = 0)

	class Meta:
		model = Category
		fields = ['name', 'views', 'likes']

class PageForm(forms.ModelForm):
	title = forms.CharField(max_length = 128, help_text = "Please enter the title of the page. ")
	url = forms.URLField(max_length = 128, help_text = "Please enter the URL of the page. ")
	views = forms.IntegerField(widget = forms.HiddenInput(), initial = 0)

	class Meta:
		model = Page
		fields = ('title', 'url', 'views')

	def clean(self):
		cleaned_data = self.cleaned_data
		url = cleaned_data.get('url')
		if url and not url.startswith('http://'):
			url = 'http://' + url 
			cleaned_data['url'] = url
		return cleaned_data

	def add_page(request, category_name_url):
		context = RequestContext(request)
		category_name = decode_url(category_name_url)
		if request.method == 'POST':
			form = PageForm(request.POST)
			if form.is_valid():
				page = form.save(commit=False)
		        try:
		        	cat = Category.objects.get(name=category_name)
		        	page.category = cat
		        except Category.DoesNotExist:
		        	return render_to_response('me/add_category.html', {}, context)
				page.views = 0
				page.save()
				return category(request, category_name_url)
			else:
				print form.errors
		else:
			form = PageForm()
		return render_to_response( 'me/add_page.html',
			{'category_name_url': category_name_url,
			'category_name': category_name, 'form': form},
			context)
