from bs4 import BeautifulSoup as bs
import pandas as pd

f = open("dependency-check-report.html", "r", encoding = "utf8")

page = f.read()

soup = bs(page)

table = soup.find("table" , attrs={"class" : "lined" , "id" : "summaryTable"})

rows = table.find_all("tr")

df = []
df.append(["Name","Cpe","Purl"])

for row in rows :
    col = row.find_all("td")
    col = [ele.text.strip() for ele in col]
    try :
        comp_name = col[0]
        cpe = col[1].replace("cpe", ",cpe").replace(",cpe", "cpe", 1)
        purl = col[2]
        df.append([comp_name,cpe,purl])

    except IndexError:
        print()

df = pd.DataFrame(df)
df.drop_duplicates(inplace = True)
df.to_csv("Report.csv", index=False, header=False)

