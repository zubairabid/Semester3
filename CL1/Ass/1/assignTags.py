import nltk
import time
import os

dev_sent = ["She has been absent since last Wednesday.", "It doesn't matter what excuse he gives me, I can't forgive him.", "I canceled my appointment because of urgent business.", "What do you do in Japan?", "The Handmaid’s Tale is an awesome piece of dystopian fiction.", "OK. Now what?", "I was laughed at by everyone.", "There were people everywhere, covering the roads along the route from the BJP headquarters to the Smriti Sthal from side to side, with security personnel maintaining strict vigil to ensure that nothing goes wrong."]

test = ["During a visit to the Cleveland Indians, Beane meets Peter Brand, a young Yale economics graduate with radical ideas about how to assess player value. Beane tests Brand's theory by asking whether he would have drafted Beane out of high school. Though scouts considered Beane hugely promising, his career in the Major Leagues was disappointing. Brand admits that, based on his method of assessing player value, he would not have drafted him until the ninth round. Impressed, Beane hires Brand as his assistant manager."]



def search(key):
	'''
	Very inefficient algorithm search
	'''
	for word in tagset:
		if key == word[0]:
			return word

def tag_all(slist):
	'''
	Returns tag list for a list. Replacement for nltk's pos_tag
	'''
	taglist = []
		for word in slist:
			taglist.append(search(word))

	return taglist



# Text Processing:
tagfile = open('CL1-2018-POS-TAGGED-DATA/english_pos_brown.txt')

filetext = tagfile.readlines()
tagset = []

# Generates the list into tagset from the file
# Very inefficient, look to improve performance
for line in filetext:
        tagset.append((line[3:-2].replace(' ','').replace('\',',',').replace(',\'',',').replace('\",',',').replace('[\'','[').replace(',,',',').replace('[','').replace('\']','').replace(',u\'',',').split(',')))

# Adding a missing comma
tagset.append([',','-HL','FW-RB-TL', '-TL', '-NC'])


