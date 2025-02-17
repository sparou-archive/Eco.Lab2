﻿#include "CEcoLab2.h"
#include "CEcoLab2Factory.h"

int16_t ECOCALLMETHOD CEcoLab2Factory_QueryInterface(IEcoComponentFactory* me, const UGUID* riid, void** ppv) {
    if ( IsEqualUGUID(riid, &IID_IEcoUnknown) || IsEqualUGUID(riid, &IID_IEcoComponentFactory) ) {
        *ppv = me;
    }
    else {
        *ppv = 0;
        return -1;
    }
    ((IEcoUnknown*)(*ppv))->pVTbl->AddRef((IEcoUnknown*)*ppv);

    return 0;
}

uint32_t ECOCALLMETHOD CEcoLab2Factory_AddRef(/* in */ IEcoComponentFactory* me) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

uint32_t ECOCALLMETHOD CEcoLab2Factory_Release(/* in */ IEcoComponentFactory* me) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        //deleteCEcoLab1Factory(&pCMe->m_VtblICF);
        return 0;
    }
    return pCMe->m_cRef;
}

int16_t ECOCALLMETHOD CEcoLab2Factory_Init(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pIUnkSystem, /* in */ void* pv) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;
    int16_t result = -1;

    if (me == 0 ) {
        return -1;
    }

    /* Инициализация компонента */
    result = pCMe->m_pInitInstance(pv, pIUnkSystem);

    return result;
}

int16_t ECOCALLMETHOD CEcoLab2Factory_Alloc(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pISystem, /* in */ struct IEcoUnknown *pIUnknownOuter, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;
    IEcoUnknown* pIUnk = 0;
    int16_t result = -1;

    if (me == 0 ) {
        return -1;
    }

    /* Агрегирование при условии если IID это IID_IEcoUnknown */
    if ( ( pIUnknownOuter != 0 ) && !IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        /* не поддерживает агрегирование */
        return -1;
    }

    /* Создание компонента */
    result = pCMe->m_pInstance(pISystem, pIUnknownOuter, (void**)&pIUnk);
    if ( result != 0 || pIUnk == 0) {
        return -1;
    }

    /* Инициализация компонента */
    result = me->pVTbl->Init(me, pISystem, pIUnk);
	
    /* Получение указателя на интерфейс */
    result = pIUnk->pVTbl->QueryInterface(pIUnk, riid, ppv);

    /* Уменьшение ссылки запрошенной Фабрикой компонентов */
    pIUnk->pVTbl->Release(pIUnk);

    return result;
}

char_t* ECOCALLMETHOD CEcoLab2Factory_get_Name(/* in */ struct IEcoComponentFactory* me) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Name;
}

char_t* ECOCALLMETHOD CEcoLab2Factory_get_Version(/* in */ struct IEcoComponentFactory* me) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Version;
}

char_t* ECOCALLMETHOD CEcoLab2Factory_get_Manufacturer(/* in */ struct IEcoComponentFactory* me) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Manufacturer;
}

/* Create Virtual Table */
IEcoComponentFactoryVTbl g_x2F5DF16EE1BF43B999A434ED38FE8F3AFactoryVTbl = {
    CEcoLab2Factory_QueryInterface,
    CEcoLab2Factory_AddRef,
    CEcoLab2Factory_Release,
    CEcoLab2Factory_Alloc,
    CEcoLab2Factory_Init,
    CEcoLab2Factory_get_Name,
    CEcoLab2Factory_get_Version,
    CEcoLab2Factory_get_Manufacturer
};


CEcoLab2Factory g_x2F5DF16EE1BF43B999A434ED38FE8F3AFactory = {
    &g_x2F5DF16EE1BF43B999A434ED38FE8F3AFactoryVTbl,
    0,
    (CreateInstance)createCEcoLab2,
    (InitInstance)initCEcoLab2,
    "EcoLab2\0",
    "1.0.0.0\0",
    "CompanyName\0"
};

#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr() {
    return (IEcoComponentFactory*)&g_x2F5DF16EE1BF43B999A434ED38FE8F3AFactory;
};
#elif ECO_LIB
IEcoComponentFactory* GetIEcoComponentFactoryPtr_2F5DF16EE1BF43B999A434ED38FE8F3A = (IEcoComponentFactory*)&g_x2F5DF16EE1BF43B999A434ED38FE8F3AFactory;
#endif