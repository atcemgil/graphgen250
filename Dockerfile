FROM python:2.7

WORKDIR /code
COPY requirements.txt ./
RUN pip install -r requirements.txt
COPY . .

EXPOSE 8880
CMD ["python", "./src/graphgen_webserver.py"]
