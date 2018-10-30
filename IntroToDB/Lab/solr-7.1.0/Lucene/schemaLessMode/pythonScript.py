from urllib2 import *
import simplejson

#default query //uses superset of lucene query syntax
query = 'http://localhost:8983/solr/gettingstarted/select?q=title_t:%22The%20Way%22'


connection = urlopen(query)
response = simplejson.load(connection)



#print response
print response['response']['numFound'], "documents found."

# Print the name of each document.
for document in response['response']['docs']:
    #print "resourcename: =", document['resourcename']
    print "id: =", document['id']
    #print '\n'
#    print "  directed_by =", document['directed_by']
#    print "  genre =", document['genre']
