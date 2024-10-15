import pandas as pd
import warnings
import re
from nltk.corpus import stopwords
nltk = __import__('nltk')
nltk.download('stopwords')

warnings.filterwarnings("ignore", category=UserWarning, module="openpyxl")

def clean_maalepinde_text(text: str, danish_stopwords: set) -> list[str]:
    text = re.sub(r'^\d+', '', text)
    text = re.sub(r'[^\w\s]', '', text)
    text = text.lower().split()

    return [word for word in text if word not in danish_stopwords]

def saml_maalepinde_for_programmering(sheet_path: str) -> list[str]:
    df = pd.read_excel(sheet_path, sheet_name=2, skiprows=1)
    filtered_df = df[df['TITEL'].str.contains('programmering', case=False, na=False)]

    danish_stopwords = set(stopwords.words('danish'))

    all_words = []

    for maalepind in filtered_df['MÅLEPIND']:
        words = clean_maalepinde_text(maalepind, danish_stopwords)
        all_words.extend(words)