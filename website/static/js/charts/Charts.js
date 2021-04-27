Chart.defaults.global.defaultFontColor = "aaa";

//Temperature Chart
let Chart1=document.getElementById('TempChart').getContext('2d');
let temperatureChart=new Chart(Chart1 ,{
  type:'line',
  data:{
    labels:["00", "01", "02", "03", "04", "05", "07", "08", "09", "10", "11", "12", "13", "14", "15", "17", "18", "19", "20", "21", "22", "23", "24"],
    datasets:[{
      label:"courbe",
      data:[26, 24, 24, 25, 23, 22, 20, 24, 23, 21, 22, 21, 20, 21, 22, 19, 20, 18, 18, 19, 20, 20, 21],
      borderColor:["#aaa"],
    }],
  },
  options:{
    title:{
      display:true,
      text:"Temperatures",
      fontColor:"#ccc"
    },
    legend:{
      display:false,
    },
  },
});

//Temperature Chart :
let Chart2=document.getElementById('HumiChart').getContext('2d');
let humidityChart=new Chart(Chart2 ,{
  type:'line',
  data:{
    labels:["00", "01", "02", "03", "04", "05", "07", "08", "09", "10", "11", "12", "13", "14", "15", "17", "18", "19", "20", "21", "22", "23", "24"],
    datasets:[{
      label:"a",
      data:[38, 37, 39, 40, 39, 38, 40, 43, 45, 44, 45, 46, 48, 52, 39, 38, 36, 35, 36, 38, 39, 41, 31],
      borderColor:["#aaa"],
    }],
  },
  options:{
    title:{
      display:true,
      text:"Humidity",
      fontColor:"#ccc"
    },
    legend:{
      display:false,
    },
  },
});