fl.outputPanel.clear();
var dom = fl.getDocumentDOM();
var lib = dom.library;
var folderURI = fl.browseForFolderURL("请选择图片所在文件夹");
if(folderURI != null)
{
	parseFolder(folderURI, "");
}
else
{
	fl.trace("取消导入");
}

function parseFolder(path, folderURL)
{
	var url = path;
	if(folderURL != null && folderURL != "")
	{
		url = path + "/" + folderURL;
	}
	fl.trace("开始解析文件夹: " + url);

	var files = FLfile.listFolder(url, "files");
	var folders = FLfile.listFolder(url, "directories");
	var file;
	var itemList = new Array();
	if(files.length > 0)
	{
		for(var i = 0;i < files.length;i ++)
		{
			var file = files[i];
			if(importable(file))
			{
				doImport(file, folderURL);
				itemList.push(file);
			}
		}
		if(itemList.length > 0)
		{
			createMc(itemList, folderURL);
		}
	}
	if(folders.length > 0)
	{
		for(var j = 0;j < folders.length;j ++)
		{
			var temp = folders[j];
			if(folderURL != null && folderURL != "")
			{
				temp = folderURL + "/" + folders[j];
			}
			if(lib.itemExists(temp) == false)
			{
				lib.newFolder(temp);
			}
			parseFolder(path, temp);
		}
	}
}
function doImport(file, folderURL)
{
	var url;
	if(folderURL == null || folderURL == "")
	{
		url = file;
	}
	else
	{
		url = folderURL + "/" + file;
	}
	if(lib.itemExists(url))
	{
		lib.deleteItem(url);
	}
	dom.importFile(folderURI + "/" + url, true);
	lib.moveToFolder(folderURL, file, true);
	//createItemMc(folderURL, file);
}

function createItemMc(folderURL, file)
{
	var temp = "Elements";
	if(folderURL != null && folderURL != "")
	{
		temp = folderURL + "/Elements";
	}
	if(lib.itemExists(temp) == false)
	{
		lib.newFolder(temp);
	}
	var path = temp + "/" + file + "_MC";
	if(lib.itemExists(path))
	{
		lib.deleteItem(path);
	}
	lib.addNewItem("movie clip", path);
	lib.editItem(path);
	if(folderURL != null && folderURL != "")
	{
		lib.selectItem(folderURL + "/" + file);
	}
	else
	{
		lib.selectItem(file);
	}
	lib.addItemToDocument({x:0, y:0})
}

function createMc(list, folderURL)
{
	var mcName = createItemName(folderURL);
	if(mcName == null)
	{
		fl.trace("不创建位图MC.");
		return;
	}
	else
	{
		if(folderURL != null && folderURL != "")
		{
			lib.editItem(folderURL + "/" + mcName);
		}
		else
		{
			lib.editItem(mcName);
		}
		var temp = fl.getDocumentDOM();
		var tl = temp.getTimeline();
		//tl.insertFrames(list.length - 1, false, 0);		
		for(var i = 0;i < list.length;i ++)
		{
			tl.currentFrame = i;
			if(folderURL != null && folderURL != "")
			{
				lib.selectItem(folderURL + list[i]);
			}
			else
			{
				lib.selectItem(list[i]);
			}
			lib.addItemToDocument({x:0, y:0});
			if(i < list.length - 1)
			{
				tl.insertBlankKeyframe(i);
			}
		}
	}
}
function createItemName(folderURL)
{
	var mcName = prompt("输入要创建的元件名称:");
	if(mcName == null)
	{
		return;
	}
	else
	{
		var temp = mcName;
		if(folderURL != null && folderURL != "")
		{
			temp = folderURL + "/" + mcName;
		}
		if(lib.itemExists(temp))
		{
			var b = confirm("库里已经有名为" + mcName + "的元件,是否替换?");
			if(b)
			{
				lib.deleteItem(temp);
				lib.addNewItem("movie clip", temp);
				return mcName;
			}
			else
			{
				return createItemName(folderURL);
			}
		}
		else
		{
			lib.addNewItem("movie clip", temp);
			return mcName;
		}
	}
	return;
}
function importable(file)
{
	var typeArr = ["png", "jpg", "gif", "bmp"];
	var temp = file.split(".");
	var type = temp[1];
	for(var i = 0;i < typeArr.length;i ++)
	{
		if(typeArr[i] == type)return true;
	}
	return false;
}
