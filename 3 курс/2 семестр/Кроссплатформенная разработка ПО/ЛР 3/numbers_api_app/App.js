import { StatusBar } from 'expo-status-bar';
import React, { useState } from 'react';
import { Button, StyleSheet, Text, TextInput, View } from 'react-native';
import RadioForm from 'react-native-simple-radio-button';

export default function App() {
  const [userInput, setUserInput] = useState('')
  const [fact, setFact] = useState('')
  const [mode, setMode] = useState('trivia')

  var radio_props = [
    {label: 'trivia', value: 'trivia' },
    {label: 'year', value: 'year' },
    {label: 'date', value: 'date' },
    {label: 'math', value: 'math' }
  ];

  return (
    <View style={styles.container}>
      <Text>
        <Text>Input a </Text>
        <Text style={styles.bold}>number</Text>
        <Text> to get some </Text>
        <Text style={styles.bold}>fact</Text>
        <Text> about it</Text>
      </Text>

      <Text>
        <Text>For </Text>
        <Text style={styles.bold}>dates</Text>
        <Text> input form is '</Text>
        <Text style={styles.bold}>5/17</Text>
        <Text>' (May 17th)</Text>
      </Text>

      <Text>
        <Text>Leave the input </Text>
        <Text style={styles.bold}>empty</Text>
        <Text> to ask for a </Text>
        <Text style={styles.bold}>random</Text>
        <Text> number</Text>
      </Text>

      <TextInput 
        placeholder='Input a number'
        style={styles.input}
        onChangeText={(val) => setUserInput(val)} />

      <RadioForm
        radio_props={radio_props}
        initial={0}
        onPress={(value) => setMode(value)}
      />

      <Button 
        title='Get fact'
        onPress={ async () => {
          number = 'random'
          if (userInput != '')
            number = userInput

          const response = await fetch('http://numbersapi.com/' + number + '/' + mode, {
            method: 'GET',
            headers: {
              Accept: 'application/json',
              'Content-type': 'application/json'
            }
          })
          const data = await response.json()
          setFact(data.text)
        }} />

      <Text style={styles.output}>
        {fact}
      </Text>

      <StatusBar style="auto" />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
  bold : {
    fontWeight: "bold"
  },
  input: {
    borderWidth: 1,
    borderColor: '#777',
    padding: 8,
    margin: 10,
    width: 200,
  },
  output: {
    borderWidth: 1,
    borderColor: '#777',
    padding: 8,
    margin: 10,
    width: 300,
    height: 100,
    textAlign: 'justify'
  }
});