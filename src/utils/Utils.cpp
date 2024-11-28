#include "utils.hpp"

DialogLayer *Odyssey::createDialog(const char *event)
{
    CCArray *arr = CCArray::create();

    //  SOLAMENTE REEMPLAZA ESTA LINEA CUANDO YA TENGAMOS EL SETTING MEJORADO
    auto spanishText = Mod::get()->getSettingValue<bool>("spanish-language");

    if (event == "on.creator")
    {
        if (!spanishText)
        {

            auto dialog_01 = DialogObject::create("????", "<s250>YOU SHALL NOT PASS</s>", 55, 1, false, {255, 255, 255});
            auto dialog_02 = DialogObject::create("????", "I'm sorry,<d010> <cy>Player...</c>", 56, 1, false, {255, 255, 255});
            auto dialog_03 = DialogObject::create("????", "You have to <cr>disable</c> the Mod to have access...", 56, 1, false, {255, 255, 255});
            auto dialog_04 = DialogObject::create("????", "Safety measures,<d020> ya know?", 53, 1, false, {255, 255, 255});
            
            arr->addObject(dialog_01);
            arr->addObject(dialog_02);
            arr->addObject(dialog_03);
            arr->addObject(dialog_04);
        }
        else
        {
            auto dialog_01 = DialogObject::create("????", "<s250>QUIETO AHI, CHAMACO.</s>", 55, 1, false, {255, 255, 255});
            auto dialog_02 = DialogObject::create("????", "Mis disculpas, <d020><cy>Jugador...</c>", 56, 1, false, {255, 255, 255});
            auto dialog_03 = DialogObject::create("????", "Tendras que <cr>deshabilitar</c> el mod para acceder al resto del juego.", 56, 1, false, {255, 255, 255});
            auto dialog_04 = DialogObject::create("????", "Medidas de seguridad, <d020>¿sabes?", 53, 1, false, {255, 255, 255});

            arr->addObject(dialog_01);
            arr->addObject(dialog_02);
            arr->addObject(dialog_03);
            arr->addObject(dialog_04);
        }
    }

    if (event == "on.shop")
    {
        if (!spanishText)
        {
            auto dialog_01 = DialogObject::create("????", "Uh, <d020>hello...", 25, 1, false, {255, 255, 255});
            auto dialog_02 = DialogObject::create("????", "Wait<d010>.<d010>.<d010>.", 24, 1, false, {255, 255, 255});
            auto dialog_03 = DialogObject::create("????", "<s250>WAIT!</s>", 20, 1, false, {255, 255, 255});
            auto dialog_04 = DialogObject::create("????", "A <cg>customer</c>! <d020>No way,<d020> a real <cg>customer</c>!<d020> I thought no one would ever come here!", 20, 1, false, {255, 255, 255});
            auto dialog_05 = DialogObject::create("????", "My name is <cp>Carp</c>,<d020> I am the shopkeeper of <cb>The Dangerous Zones</c>.", 21, 1, false, {255, 255, 255});
            auto dialog_06 = DialogObject::create("Carp", "Why do I live here?<d020> Well,<d020> let's just say I found out <cr>something I shouldn't have</c><d010>.<d010>.<d010>.", 22, 1, false, {255, 255, 255});
            auto dialog_07 = DialogObject::create("Carp", "Don't check <cy>RubRub's</c> computer search history...", 23, 1, false, {255, 255, 255});
            auto dialog_08 = DialogObject::create("Carp", "As a punishment,<d020> I was removed from the community shop and sent here.", 22, 1, false, {255, 255, 255});
            auto dialog_09 = DialogObject::create("Carp", "I have a lot of stuff to sell!<d020> So if you need anything you can get it here!", 20, 1, false, {255, 255, 255});
            auto dialog_10 = DialogObject::create("Carp", "Or not<d010>.<d010>.<d010>.", 19, 1, false, {255, 255, 255});

            arr->addObject(dialog_01);
            arr->addObject(dialog_02);
            arr->addObject(dialog_03);
            arr->addObject(dialog_04);
            arr->addObject(dialog_05);
            arr->addObject(dialog_06);
            arr->addObject(dialog_07);
            arr->addObject(dialog_08);
            arr->addObject(dialog_09);
            arr->addObject(dialog_10);
        }
        else
        {
            auto dialog_01 = DialogObject::create("????", "Uh, hola...", 25, 1, false, {255, 255, 255});
            auto dialog_02 = DialogObject::create("????", "Espera<d010>.<d010>.<d010>.", 24, 1, false, {255, 255, 255});
            auto dialog_03 = DialogObject::create("????", "<s250>ESPERA!</s>", 20, 1, false, {255, 255, 255});
            auto dialog_04 = DialogObject::create("????", "Un <cg>cliente!</c><d020> No puede ser, es un cliente!<d020> Crei que nadie llegaria aqui jamas.", 20, 1, false, {255, 255, 255});
            auto dialog_05 = DialogObject::create("????", "Me llamo <cp>Carp</c>, soy el shopkeeper de <cb>The Dangerous Zones</c>.", 21, 1, false, {255, 255, 255});
            auto dialog_06 = DialogObject::create("Carp", "¿Por que vivo aqui?<d020> Bien,<d020> digamos que me entere de algo que no debi<d010>.<d010>.<d010>.", 22, 1, false, {255, 255, 255});
            auto dialog_07 = DialogObject::create("Carp", "No revises el historial de busqueda de la computadora de <cy>RubRub</c>.", 23, 1, false, {255, 255, 255});
            auto dialog_08 = DialogObject::create("Carp", "Como castigo,<d020> me retiraron de la tienda comunitaria y me enviaron aqui.", 22, 1, false, {255, 255, 255});
            auto dialog_09 = DialogObject::create("Carp", "¡Tengo muchas cosas para vender!<d020> Asi que si necesitas algo puedes conseguirlo aqui!", 20, 1, false, {255, 255, 255});
            auto dialog_10 = DialogObject::create("Carp", "O no<d010>.<d010>.<d010>.", 19, 1, false, {255, 255, 255});

            arr->addObject(dialog_01);
            arr->addObject(dialog_02);
            arr->addObject(dialog_03);
            arr->addObject(dialog_04);
            arr->addObject(dialog_05);
            arr->addObject(dialog_06);
            arr->addObject(dialog_07);
            arr->addObject(dialog_08);
            arr->addObject(dialog_09);
            arr->addObject(dialog_10);
        }
    }

    auto dialogLayer = DialogLayer::createDialogLayer(nullptr, arr, 2);
    dialogLayer->animateInRandomSide();
    dialogLayer->setZOrder(2);

    return dialogLayer;
};