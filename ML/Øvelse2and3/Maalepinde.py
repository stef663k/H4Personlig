import pandas as pd
import warnings
import re
from nltk.corpus import stopwords
from collections import Counter
from wordcloud import WordCloud  
import matplotlib.pyplot as plt
import numpy as np
nltk = __import__('nltk')
nltk.download('stopwords')

warnings.filterwarnings("ignore", category=UserWarning, module="openpyxl")

# def roman_to_int(roman: str) -> int:
#     roman_dict = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100}
#     total = 0
#     prev = 0
#     for char in reversed(s):
#         value = roman_dict[char]
#         if value < prev:
#             total -= value
#         else:
#             total += value
#         prev = value
#     return total

def clean_maalepinde_text(text: str, danish_stopwords: set) -> str:
    text = re.sub(r'^\d+\.', '', text)
    text = re.sub(r'[^\w\s]', '', text) 
    text = re.sub(r'\d+', '', text) 
    text = re.sub('\n\n', '\n', text)
    text = text.lower()
    words = text.split()
    cleaned_text = ' '.join([word for word in words if word not in danish_stopwords])
    return cleaned_text

def saml_maalepinde_for_programmeringsuddannelsen(sheet_path: str, sheet_names: list) -> list[str]:
    danish_stopwords = set(stopwords.words('danish'))
    
    all_cleaned_maalepinde = []
    
    for sheet in sheet_names:
        df = pd.read_excel(sheet_path, sheet_name=sheet, skiprows=1, engine='openpyxl')
        
        unwanted_categories = ['Grundfag', 'htx', 'hf', 'EUX-fag', 'hhx', 'Kompetencemål', 'Oplæringsmål', 'Afsluttende prøve']
        df = df[~df['FAGKATEGORI'].isin(unwanted_categories)]
        df = df.sort_values(by=['TITEL', 'NIVEAU'], ascending=False)
        df = df[df['RESULTATFORM'] == '-/STA/7TRIN']
        df=df.drop_duplicates(subset=['TITEL'], keep='first')
        df = df.dropna(subset=['MÅLPINDE'])
        df = df[~df['MÅLPINDE'].str.isspace()]
        
        for index, row in df.iterrows(): 
            maalepind_lines = row['MÅLPINDE'].split('\n')
            nummer = row['NUMMER']
            titel = row['TITEL']
            for line in maalepind_lines:
                cleaned_maalepind = clean_maalepinde_text(line, danish_stopwords)
                if cleaned_maalepind: 
                    all_cleaned_maalepinde.append((nummer, titel, cleaned_maalepind))  
    
    return all_cleaned_maalepinde

def separate_maalepinde(maalepinde):
    separated_maalepinde = []
    for nummer, titel, maalepind in maalepinde:
        split_maalepinde = re.split(r'\.\s', maalepind)
        for item in split_maalepinde:
            if item.strip(): 
                separated_maalepinde.append((nummer, titel, item.strip())) 
    return separated_maalepinde

sheet_path = './data/Fagtabel2024.xlsx'
sheet_names = ['Datatekniker med speciale i pro']  

cleaned_programming_maalepinde = saml_maalepinde_for_programmeringsuddannelsen(sheet_path, sheet_names)

separated_maalepinde = separate_maalepinde(cleaned_programming_maalepinde)

df_output = pd.DataFrame(separated_maalepinde, columns=['NUMMER', 'TITEL', 'MÅLPINDE'])

output_path = './data/maalepinde_output.xlsx'
df_output.to_excel(output_path, index=False)



for nummer, titel, maalepind in separated_maalepinde:
    print(f'NUMMER: {nummer}, TITEL: {titel}, MÅLPINDE: {maalepind}')
total_words = 0
print("Letters from MÅLPINDE")

total_maalepinde = len(separated_maalepinde)
print(f'Total separated maalepinde: {total_maalepinde}')
print(f'Output saved to {output_path}')

for _, _, maalepind in separated_maalepinde:
    words = maalepind.split()
    for word in words:
        # print(letter)
        new_word = re.sub(r'\W+', '', word)
        # print (f'Total letters: {new_word}')
        total_words += 1
print(f'Total words: {total_words}')


word_counter = Counter()
for _, _, maalepind in separated_maalepinde:
    words = maalepind.split()
    word_counter.update(words)

most_common_words = word_counter.most_common(30)

print("\n30 most common words")
for word, count in most_common_words:
    print(f'{word}: {count}')

words, counts = zip(*most_common_words)

plt.figure(figsize=(10, 5))
plt.bar(words, counts, color='skyblue')
plt.xlabel('words')
plt.ylabel('counts')
plt.xticks(rotation=45)
plt.title('30 most common words')
plt.show()

all_text= ' '.join([maalepind for _, _, maalepind in separated_maalepinde])
wc = WordCloud(background_color='black', width=800, height=500, collocations=False).generate(all_text)
plt.axis('off')
plt.imshow(wc, interpolation='bilinear')
plt.show()