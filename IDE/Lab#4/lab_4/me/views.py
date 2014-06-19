from django.http import HttpResponse
from django.template import RequestContext
from django.shortcuts import render_to_response, render
from me.models import Category, Page
from me.forms import CategoryForm, PageForm

# Create your views here.
def index(request):
	context = RequestContext(request)
	category_list = Category.objects.order_by('-likes')[:5]
	page_list = Page.objects.order_by('-views')[:5]
	for category in category_list:
		category.url = category.name.replace(' ', '_')
	context_dict = {
		'categories': category_list, 
		'pages': page_list
	}
	return render_to_response('me/index.html', context_dict, context)

def about(request):
	context = RequestContext(request)    	
	context_dict = {'italicmessage': 'I am italic font from context'}
	return render_to_response('me/about.html', context_dict, context)

def category(request, category_name_url):
	context = RequestContext(request)
	category_name = category_name_url.replace('_', ' ')
	context_dict = {'category_name': category_name, 
					'category_name_url' : category_name_url}

	try:
		category = Category.objects.get(name = category_name)
		pages = Page.objects.filter(category = category)
		context_dict['pages'] = pages
		context_dict['category'] = category
	except Category.DoesNotExist:
		pass
	return render_to_response('me/category.html', context_dict, context)

def pages(request, page_name):
	context = RequestContext(request)
	context_dict = {'page_name' : page_name}

	try:
		page = Page.objects.get(name = page_name)
		context_dict['page'] = page
	except Page.DoesNotExist:
		pass
	return render_to_response('page.url', context_dict, context)

def add_category(request):
	context = RequestContext(request)
	if request.method == "POST":
		form = CategoryForm(request.POST)
		if form.is_valid():
			form.save()
			return index(request)
		else:
			print form.errors
	else:
		form = CategoryForm()
	return render_to_response ('me/add_category.html', {'form': form}, context)