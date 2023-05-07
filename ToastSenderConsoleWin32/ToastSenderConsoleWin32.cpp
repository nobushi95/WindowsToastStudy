#include <iostream>

#include "DesktopNotificationManagerCompat.h"
#include <NotificationActivationCallback.h>
#include <windows.ui.notifications.h>

using namespace ABI::Windows::Data::Xml::Dom;
using namespace ABI::Windows::UI::Notifications;
using namespace Microsoft::WRL;

// The UUID CLSID must be unique to your app. Create a new GUID if copying this code.
class DECLSPEC_UUID("a8a47616-b67f-4fd1-8a96-bdc29c84b7e5") NotificationActivator WrlSealed WrlFinal
    : public RuntimeClass<RuntimeClassFlags<ClassicCom>, INotificationActivationCallback>
{
public:
    virtual HRESULT STDMETHODCALLTYPE Activate(
        _In_ LPCWSTR appUserModelId,
        _In_ LPCWSTR invokedArgs,
        _In_reads_(dataCount) const NOTIFICATION_USER_INPUT_DATA * data,
        ULONG dataCount) override
    {
        // TODO: Handle activation
    }
};

// Flag class as COM creatable
CoCreatableClass(NotificationActivator);

int main()
{
    std::cout << "Send Toast" << std::endl;

    // Register activator type
    auto hr = DesktopNotificationManagerCompat::RegisterActivator();

    // Construct XML
    ComPtr<IXmlDocument> doc;
    auto hr = DesktopNotificationManagerCompat::CreateXmlDocumentFromString(
        L"<toast><visual><binding template='ToastGeneric'><text>Hello world</text></binding></visual></toast>",
        &doc);
    if (SUCCEEDED(hr))
    {
        // See full code sample to learn how to inject dynamic text, buttons, and more

        // Create the notifier
        // Desktop apps must use the compat method to create the notifier.
        ComPtr<IToastNotifier> notifier;
        hr = DesktopNotificationManagerCompat::CreateToastNotifier(&notifier);
        if (SUCCEEDED(hr))
        {
            // Create the notification itself (using helper method from compat library)
            ComPtr<IToastNotification> toast;
            hr = DesktopNotificationManagerCompat::CreateToastNotification(doc.Get(), &toast);
            if (SUCCEEDED(hr))
            {
                // And show it!
                hr = notifier->Show(toast.Get());
            }
        }
    }
    std::cout << "enter any charactor to finish ..." << std::endl;
    std::string finish;
    std::cin >> finish;
}
