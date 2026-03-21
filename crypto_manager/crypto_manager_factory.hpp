/// @file
/// @brief Объявление фабрики для менеджера криптографических операций.
/// @author Artemenko Anton
#ifndef GUID_DEA1E190_A43E_4746_AAB4_44380D2D63C1
#define GUID_DEA1E190_A43E_4746_AAB4_44380D2D63C1

#include <crypto_strategy_factory.hpp>
#include <icrypto_manager.hpp>

#include <memory>

namespace crypto_manager
{
/// @brief Создает менеджер криптографических операций с указанной стратегией.
/// @param[in] cryptoStrategy Конкретная крипто-стратегия.
/// @return Умный указатель на менеджер криптографических операций.
std::shared_ptr<ICryptoManager> CreateCryptoManager(std::unique_ptr<ICryptoStrategy> cryptoStrategy);

/// @brief Создает менеджер криптографических операций по выбранному backend'у.
/// @param[in] backend Идентификатор криптографического backend'а.
/// @return Умный указатель на менеджер криптографических операций.
std::shared_ptr<ICryptoManager> GetCryptoManager(CryptoBackend backend);

/// @brief Создает менеджер криптографических операций с backend'ом по умолчанию.
/// @return Умный указатель на менеджер криптографических операций.
std::shared_ptr<ICryptoManager> GetCryptoManager();

} // namespace crypto_manager

#endif // GUID_DEA1E190_A43E_4746_AAB4_44380D2D63C1