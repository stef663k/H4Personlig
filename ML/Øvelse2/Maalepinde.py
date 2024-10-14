import pandas as pd
import warnings

warnings.filterwarnings("ignore", category=UserWarning, module="openpyxl")

def hent_maalepinde(fagnr: int) -> list[str]:
    df = pd.read_excel('data/Fagtabel.xlsx', skiprows=1)
    print(df.columns)
    return df[df['NUMMER'] == fagnr]['TITEL'].tolist()

ml = hent_maalepinde(17348)
sw_test = hent_maalepinde(16484)

for m in ml:
    print("ml", m)

for m in sw_test:
    print("test: ", m)
   
