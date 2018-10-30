from urllib2 import *
import simplejson
connection = urlopen('http://localhost:8983/solr/films/select?fl=name%20directed_by&fq=genre:%22Superhero%20movie%22&q=*:*&sort=initial_release_date%20desc')
response = simplejson.load(connection)
print response['response']['numFound'], "documents found."									
# Print the name of each document.

for document in response['response']['docs']:
	print "  Name =", document['name']
	print "  Directed_by =", document['directed_by']

