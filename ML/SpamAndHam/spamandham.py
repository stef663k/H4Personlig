import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split , GridSearchCV , KFold
from sklearn.svm import SVC 
from sklearn.metrics import accuracy_score , classification_report , confusion_matrix
import seaborn as sns
import matplotlib.pyplot as plt
import re
import nltk
from nltk.stem import PorterStemmer
from sklearn import metrics
from sklearn.feature_extraction.text import CountVectorizer
from imblearn.under_sampling import NearMiss
from collections import Counter
from imblearn.over_sampling import RandomOverSampler
import warnings
warnings.filterwarnings('ignore', category=UserWarning, module='sklearn')


df_csv = pd.read_csv("https://raw.githubusercontent.com/Sanjay-dev-ds/spam_ham_email_detector/master/spam.csv")
df_csv.head()
df = df_csv.drop_duplicates(keep='first')


df_excel = pd.read_excel("./data/maalepinde_output.xlsx")

print(f"Email data shape: {df_csv.shape}")
print(f"Maalepinde data shape: {df_excel.shape}")

df_combined = pd.merge(df_csv, df_excel, how='left', left_index=True, right_index=True)

print(f"Combined data shape: {df_combined.shape}")

print(df_combined.columns)
print(df_combined.dtypes)
print(df_combined['MÅLPINDE'].isnull().sum())

df_combined['MÅLPINDE'] = df_combined["MÅLPINDE"].fillna('N/A')

df_combined['CombinedText'] = df_combined['EmailText'] + ' ' + df_combined['MÅLPINDE'].astype(str)

porter_stemmer = PorterStemmer()
def preprocessor(text):
    text=text.lower()
    text=re.sub("\\W", " ", text)
    text=re.sub("\\s+(in|the|all|for|and|on)\\s+"," _connector_ ", text)
    words=re.split("\\s+", text)
    stemmed_text=[porter_stemmer.stem(word=word) for word in words]
    return ' '.join(stemmed_text)


def tokenizer(text):
    text=re.sub("(\\W)"," \\1 ", text)
    return re.split("\\s+", text)

vectorizer = CountVectorizer(tokenizer=tokenizer,ngram_range=(1,2),min_df=0.006,preprocessor=preprocessor)
x_combined = vectorizer.fit_transform(df_combined['CombinedText']).toarray()

print(df_combined[['EmailText', 'MÅLPINDE', 'CombinedText']].head())
y = df_combined['Label'].values

print(f"Combined data shape: {x_combined.shape}")
print(f"Target variabel shape: {y.shape}")

ros = RandomOverSampler(random_state=42)
x_combined, y = ros.fit_resample(x_combined, y)

print('Modified dataset shape', Counter(y))

sns.countplot(df['Label'])
# plt.show()

x_train, x_test, y_train, y_test = train_test_split(x_combined, y, test_size=0.2, random_state=0)

model = SVC(C =1, kernel='linear')
model.fit(x_train, y_train)

accuracy = metrics.accuracy_score(y_test, model.predict(x_test))

print(f'Accuracy: {accuracy:.2f}%')
print(classification_report(y_test, model.predict(x_test)))

params = {"C":[0.2,0.5], "kernel":["linear","poly","rbf"]}
cval = KFold(n_splits = 2)
model = SVC()
TunedModel = GridSearchCV(model,params,cv= cval)

TunedModel.fit(x_train, y_train)

accuracy = metrics.accuracy_score(y_test, TunedModel.predict(x_test))
accuracy_percentage = 100 * accuracy
accuracy_percentage

sns.heatmap(confusion_matrix(y_test, TunedModel.predict(x_test)), annot=True, fmt ="g",cmap="Blues")
plt.xlabel('Predicted')
plt.ylabel('Actual')
plt.title('Confusion Matrix')
plt.show()

print(classification_report(y_test, TunedModel.predict(x_test)))


mails = ["Hey, you have won a car !!!!. Conrgratzz"
              ,"Dear applicant, Your CV has been recieved. Best regards"
              ,"You have received $1000000 to your account"
              ,"Join with our whatsapp group"
              ,"Kindly check the previous email. Kind Regard"]
for mail in mails:
    is_spam = TunedModel.predict(vectorizer.transform([mail]).toarray())
    print(mail + " : " + is_spam)

