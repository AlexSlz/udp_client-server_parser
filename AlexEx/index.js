const mainElement = document.createElement('div')
mainElement.classList.add('mainElement', 'hide')
mainElement.innerHTML = '<h1 id="text">Alex:)</h1>'
document.body.appendChild(mainElement)

const log = document.getElementById('text')
let port
let readBool

chrome.runtime.onMessage.addListener((msgObj) => {
  if (msgObj === 'modal') {
    if (mainElement.classList.contains('hide'))
      mainElement.classList.remove('hide')
    else mainElement.classList.add('hide')
  }
  if (msgObj === 'start') {
    if (navigator.serial) {
      connectSerial()
    } else {
      alert('Web Serial API not supported :(')
    }
  }
})

async function connectSerial() {
  readBool = true
  try {
    port = await navigator.serial.requestPort()
    await port.open({ baudRate: 9600 })
    console.log('conn...')
  } catch (error) {
    console.log('port: ' + error)
  }
  if (port != undefined) readPort()
  readSite()
}

async function closeSerial() {
  readBool = false
  if (!reader) reader.cancel()
  //await port.close()
  console.log('serial closed')
}

let dataOldLen = 0

async function readSite() {
  let myInt = setInterval(() => {
    try {
      let dataList = document
        .querySelector('.code_panel__serial__content__text')
        .innerHTML.split('\r\n')
      let data = dataList[dataList.length - 2]
      if (dataList.length - 1 != dataOldLen && data != undefined) {
        dataOldLen = dataList.length - 1
        sendPortMsg(data)
        //document.querySelector('.js-code_panel__serial__clear').click()
      }
    } catch (error) {
      console.log('element not found')
      clearInterval(myInt)
      closeSerial()
    }
  }, 1000)
}

async function sendPortMsg(msg) {
  const textEncoder = new TextEncoderStream()
  const writableStreamClosed = textEncoder.readable.pipeTo(port.writable)

  const writer = textEncoder.writable.getWriter()

  await writer.write(msg + '\n')
  writer.close()
  await writableStreamClosed
}
let reader
async function readPort() {
  const textDecoder = new TextDecoderStream()
  const readableStreamClosed = port.readable.pipeTo(textDecoder.writable)

  while (readBool) {
    let msg = ''
    reader = textDecoder.readable.getReader()
    while (readBool) {
      let { value, done } = await reader.read()
      if (value) {
        msg += value
      }
      if (value && value.indexOf('\n') > -1) {
        done = true
      }
      if (done) {
        log.innerHTML = '<h1>Message from Port</h1> <hr/>' + msg
        inputSend(msg)
        reader.releaseLock()
        break
      }
    }
  }
  await readableStreamClosed.catch((error) => {
    console.log(error)
  })
}

async function inputSend(msg) {
  try {
    let input = document.querySelector('.code_panel__serial__input')
    input.value = msg
    document.querySelector('.js-code_panel__serial__send').click()
  } catch (error) {
    console.log('errod... addElement: ' + error)
  }
}
