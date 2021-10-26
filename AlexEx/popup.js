document.getElementById('btn').addEventListener('click', () => {
  sendMessage('modal')
})
document.getElementById('connect').addEventListener('click', () => {
  sendMessage('start')
})

function sendMessage(message) {
  chrome.tabs.query({ active: true, currentWindow: true }, (tabs) => {
    chrome.tabs.sendMessage(tabs[0].id, message)
  })
}
