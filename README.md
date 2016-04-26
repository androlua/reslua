#reslua
许多工具导出的资源描述是xml、json等，游戏是lua写的。

lua的一个优势就是既可以写逻辑，也可以写配置，如果资源描述也是lua的话，我就不用花时间找库去在运行时解析json、xml。

##本工具的目标
像一个编译器一样工作，把xml、json提前转换成lua格式。

##JSON

test.json
  
    {
  	  "元件 2":{
  		  "type":"group",
  		  "children":{
  			  "图层 2":{
  				  "id":"元件 1",
  				  "x":14.05,
  				  "y":159.15,
  				  "angle":17.7474365234375,
  				  "sx":1.0000152587890625,
  				  "sy":1.0000152587890625
  			  },
  			  "图层 1":{
    				"id":"元件 1",
    				"x":-56,
    				"y":-69,
    				"angle":0,
    				"sx":1,
    				"sy":1
    			}
    		}
    	},
    	"元件 1":{
    		"type":"sprite",
    		"frameName":"元件 10000"
    	},
    	"元件 3":{
    		"type":"sprite",
    		"frameName":"元件 30000"
    	}
    }
    
**运行：** cat test.json|./json > test.lua

结果生成 test.lua

    local retJSON = {
    	["元件 2"] = {
    		["type"] = "group",
    		["children"] = {
    			["图层 2"] = {
    				["id"] = "元件 1",
    				["x"] = 14.050000,
    				["y"] = 159.149994,
    				["angle"] = 17.747437,
    				["sx"] = 1.000015,
    				["sy"] = 1.000015
    			},
    			["图层 1"] = {
    				["id"] = "元件 1",
    				["x"] = -56.000000,
    				["y"] = -69.000000,
    				["angle"] = 0.000000,
    				["sx"] = 1.000000,
    				["sy"] = 1.000000
    			}
    		}
    	},
    	["元件 1"] = {
    		["type"] = "sprite",
    		["frameName"] = "元件 10000"
    	},
    	["元件 3"] = {
    		["type"] = "sprite",
    		["frameName"] = "元件 30000"
    	}
    }
    return retJSON
    
**现在可以使用 local res = require 'test' 加载资源**

##XML 开发中。。。
