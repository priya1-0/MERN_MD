from bs4 import BeautifulSoup as bs
import pandas as pd
import csv
f = open("dependency-check-report.html", "r", encoding = "utf8")
page = f.read()
soup = bs(page)
table = soup.find("table" , attrs={"class" : "lined" , "id" : "summaryTable"})
rows = table.find_all("tr")
print(rows)
# td = table.find_all("td")
# print(td)
# data-sort-value
# import nltk
# nltk.download('punkt')
# from nltk.tokenize import word_tokenize,sent_tokenize
# tokenizer = sent_tokenize
# print(tokenizer.tokenize(rows))


df = []
df.append(["Name","Cpe","Purl","Version","Type", "Supplier","license",'Description' ])


print(df)


for row in rows :
    col = row.find_all("td")
    col = [ele.text.strip() for ele in col]
    try :
        comp_name = col[0]
        cpe = col[1].replace("cpe", ",cpe").replace(",cpe", "cpe", 1)
        purl = col[2]
        version = purl[purl.find("@")+1:]
        df.append([comp_name,cpe,purl,version])

    except IndexError:
        print()

df = pd.DataFrame(df)
print(df)

df.to_csv("Report.csv", index=False,header=False)
#

# df = pd.read_csv("dependency-check-report.csv", usecols = ['Description'])

# # print(df)
# data = df
# print(data)
# df = pd.DataFrame(data)
# df.to_csv('Report.csv', mode='a', index=False, header=False)
# # df.to_csv('Report.csv', mode='a',columns=['Description'])
# # df.to_csv('Report.csv', mode='a', index=False, header=False)

df2 = pd.read_csv("dependency-check-report.csv", usecols = ['DependencyName','Description'])
df2 = pd.DataFrame(df2)
print(df2)
df = pd.read_csv("Report.csv",header=0)
print(df)
# df2.to_csv("Report2.csv", index=False)

df2 = pd.read_csv("dependency-check-report.csv", usecols = ['DependencyName','Description'])

df2 = pd.DataFrame(df2)
print(df2)

df = pd.read_csv("Report.csv",header=0)
print(df)
df["Type"] = df["Type"].apply(lambda x: "Library")
df2 = pd.read_csv("dependency-check-report.csv", usecols = ['DependencyName','Description'])

print(df2)
df2.index = df2.index.astype(str)
df.index = df.index.astype(str)

df = df.join(df2.set_index('DependencyName'), on='Name', how="left", lsuffix='_left', rsuffix='')
print(df)
del df['Description_left']
print(df)

# df = df.reindex_like(df2).assign(**{'Description': df2['Description']})
df.to_csv("SoupList.csv", index=False)

stdout = "soup list generated"








# with open('dependency-check-report.csv', 'r') as f1, open('Report.csv', 'a+') as f2:
#     f2.write(f1.read(col[3]))



# df = pd.read_csv("dependency-check-report.csv", usecols = ['Description'])
# # print(df)
# data = df
# print(df)
# df.to_csv('Report.csv', mode='a',columns=['Description'])







