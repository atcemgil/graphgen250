FROM python:2.7

WORKDIR /code
COPY requirements.txt ./
RUN pip install -r requirements.txt
COPY src .
RUN make

EXPOSE 8880
CMD ["python", "graphgen_webserver.py"]
