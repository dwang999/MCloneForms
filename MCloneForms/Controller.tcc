// Controller.tcc

#ifndef CONTROLLER_TCC_INCLUDED
#define CONTROLLER_TCC_INCLUDED

// Constructors
template <typename T> Controller<T>::Controller(std::string profileName, std::string controllerName, std::string fileName, std::string backupFileName) : 
	profileName(profileName), controllerName(controllerName), fileName(fileName), backupFileName(backupFileName){}

// Methods

template <typename T> bool Controller<T>::saveController(std::string fileString)
{
	std::fstream fs;
	fs.open(fileString, std::fstream::out | std::fstream::trunc);

	if (fs.is_open())
	{
		for(T t: vectorT)
		{
			fs << t << std::endl;
		} 

		fs.close();
		return true;
	}
	else
		return false;
};

// Save Controller and delete the backup
template<typename T> void Controller<T>::save()
{
	if(saveController(fileName))
	{
		if (backupExists())
		{
			if(!deleteBackup())
				throw std::runtime_error("EarningController<T>::save : Entries backup was not deleted");
		}
	}
	else
		throw std::runtime_error("EarningController<T>::save : Entries save file could not be opened");
}

template<typename T> void Controller<T>::autoSave()
{
	if(!saveController(backupFileName))
		throw std::runtime_error("EarningController<T>::save : Entries save file could not be opened");
}

template<typename T> void Controller<T>::remove(int indexToRemove)
{

	vectorT.erase(vectorT.begin() + indexToRemove);
}


template<typename T> int Controller<T>::generateID()
{
	if (vectorT.empty())
		return 1;
	else
	{
		int largest = 0;
		for (size_t i = 0; i < vectorT.size(); i++)
		{
			if (vectorT[i].id > largest)
				largest = vectorT[i].id;
		}

		return largest + 1;

	}
}


template<typename T> void Controller<T>::add(T t)
{

	vectorT.push_back(t);
}

template<typename T> void Controller<T>::loadController( std::string fileName)
	{		
		std::fstream fs;
		std::string line;

		fs.open(fileName, std::fstream::in);


		if (fs.is_open())
		{
			while(!fs.eof())
			{
				std::getline(fs, line);
				if (!line.empty())
				{
					this->add(T::parseTokens(line));
				}

			}
			fs.close();
		}
	}

template<typename T> bool Controller<T>::backupExists()
{
	std::ifstream ifile(backupFileName.c_str());
	if(ifile.good())
	{
		ifile.close();
		return true;
	}
	else
		return false;
}

template<typename T> bool Controller<T>::deleteBackup(){
	if(std::remove(backupFileName.c_str()) != 0)
		return false;
	else
		return true;
}

#endif

