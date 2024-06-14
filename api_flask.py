#!/usr/bin/python
# coding: utf-8
from flask import Flask, request, jsonify

app = Flask(__name__)
data = []

@app.route('/sensor/data', methods=['POST'])
def post():
    temperature = request.args.get("temperature")
    kelembapan = request.args.get("kelembapan")
    subData = {"temperature": temperature, "kelembapan": kelembapan}
    
    data.append(subData)
    return 'Berhasil disimpan ke server'

@app.route('/sensor/data', methods=['GET'])
def get():
    return jsonify(data)

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
